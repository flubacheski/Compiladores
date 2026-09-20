/*

Gramatica notacao EBNF
<expressao>::= <termo> {('+'|'-') <termo>}
<termo>::=<fator> {('*'|'/') <fator>}
<fator>::='a'|'b'|'c'|...|'1'|'2'|'3'|...|'('<expressão>')'

Implementacao da gramatica para gerar codigo intermediario
gcc gera_mepa.c -o gera_mepa
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// variavel global do analisador lexico
//char *buffer ="a+(b/9-3)*c"; // posfixa a b 9 / 3 - c * +
//char *buffer ="a+b"; // posfixa a b +
char *buffer;

// variavel global do analisador sintatico
char lookahead;

//<expressao>::= <termo> {('+'|'-') <termo>}
//<termo>::=<fator> {('*'|'/') <fator>}
//<fator>::='a'|'b'|'c'|...|'1'|'2'|'3'|...|'('<expressão>')'
// prototipacao de funcao
void expressao(); 
void termo();
void fator();
void consome( char atomo );

int main(int nArgs, char **Args){
    if( nArgs < 2 ){
        printf("%s\nErro na chamada do programa\nuse: ./gera_mepa <expressao infixa>\n",Args[0]);
        exit(1);
    }
    buffer = Args[1];
    printf("infixa : %s\n",buffer);
    printf("MEPA\n\n");
    
    lookahead = *buffer++; //obter_átomo
    expressao(); // chama o simbolo inicial da gramatica

    consome('\0');

    printf("\n\nfim de programa.\n");

    return 0;
}
void consome( char atomo ){
    if( lookahead == atomo )
        lookahead =*buffer++; // obter_atomo();  analisador lexico
    else{
        // tratador de erros
        printf("Erro sintatico: esperado [%c] encontrado [%c]\n",atomo,lookahead);
        exit(1);
    }
}

//<expressao>::= <termo> {('+'|'-') <termo>}
void expressao(){
    termo();
    while(lookahead == '+' || lookahead == '-'){
        char operador = lookahead;
        consome(lookahead);
        termo();
        if(operador == '+')
            printf("SOMA\n");
        else
            printf("SUBT\n");

    }
}
//<termo>::=<fator> {('*'|'/') <fator>}
void termo(){
    fator();
    while(lookahead == '*' || lookahead == '/'){
        char operador = lookahead;
        consome(lookahead);
        fator();
        if(operador == '*')
            printf("MULT\n");
        else
            printf("DIVI\n");


    }
}
//<fator>::='a'|'b'|'c'|...|'1'|'2'|'3'|...|'('<expressão>')'
void fator(){
    if(isdigit(lookahead)){
        printf("CRCT %c\n",lookahead);
        consome(lookahead);
    }
    else if(isalpha(lookahead)){
        printf("CRVL %c\n",lookahead);
        consome(lookahead);
    }
    else{
        consome('(');
        expressao();
        consome(')');
    }
}
