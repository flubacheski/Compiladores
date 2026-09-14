/*
Gramatica na notacao BNF
<expressao>::=<expressao>'+'<termo>|<expressão>'-'<termo>|<termo>
<termo>::=<termo> '*'<fator>|<termo>'/'<fator>|<fator>
<fator>::='a'|'b'|'c'|...|'1'|'2'|'3'|...|'('<expressão>')'

Converter para notacao EBNF
fatorar a esquerda
<expressao>::=<expressao> ('+'<termo>|'-'<termo>) <termo>

fatorar a direita
<expressao>::= <expressao> ('+'|'-') <termo> !  <termo>

eliminando a recursividade a esquerda
<expressao>::= <termo> {('+'|'-') <termo>}

<termo>::=<termo> ('*'|'/') <fator>|<fator>

Gramatica notacao EBNF
<expressao>::= <termo> {('+'|'-') <termo>}
<termo>::=<fator> {('*'|'/') <fator>}
<fator>::='a'|'b'|'c'|...|'1'|'2'|'3'|...|'('<expressão>')'

gcc ASDR3.c -o ASDR3
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// variavel global do analisador lexico
char *buffer ="a+1*(b-3)"; // posfixa a 1 b 3 - * +

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

int main(){
    printf("Analisando: %s => ",buffer);
    lookahead = *buffer++; //obter_átomo
    expressao(); // chama o simbolo inicial da gramatica

    consome('\0');

    printf("fim de programa.\n");

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
        consome(lookahead);
        termo();
    }
}
//<termo>::=<fator> {('*'|'/') <fator>}
void termo(){
    fator();
    while(lookahead == '*' || lookahead == '/'){
        consome(lookahead);
        fator();
    }
}
//<fator>::='a'|'b'|'c'|...|'1'|'2'|'3'|...|'('<expressão>')'
void fator(){
    if(isdigit(lookahead)){
        consome(lookahead);
    }
    else if(isalpha(lookahead)){
        consome(lookahead);
    }
    else{
        consome('(');
        expressao();
        consome(')');
    }
}
