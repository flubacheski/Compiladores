#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
/*
ASDR para gramatica
E ::= E + F | E - F | F
E ::= E (+|-) F | F => gramatica fatorada a esquerda
E::= F { (+|-)F } => gramatica com eliminacao de recursividade a esquerda

F ::= num


*/

//char *buffer="abaddc";
char *buffer="1+2-3+4+5-6+v";// aceita essa palavra
char lookahead; // simbolo no inicio da cadeia
void consome( char atomo );
void E();
void F();

int main(void){
    printf("analisando %s\n",buffer);
    //inicializa a variavel global com o primeiro simbolo no inicio do buffer.
    //e anda com o buffer, ou seja, atualiza uma posicao pra frente o buffer
    lookahead = *buffer++;
    E();
    if( lookahead == '\x0')// fim de buffer
        printf("palavra aceita.");
    else
        printf("\nerro sintatico.");

    printf("\nfim de programa.\n");
    return 0;
}
// verifica se o parametro atomo casa com o simbolo no inicio do buffer
// caso seja o simbolo esperado a variavel lookahead e atualiza com o inicio do buffer
void consome( char atomo ){
    //erifica se o parametro atomo casa com o simbolo no inicio do buffer
    if( lookahead == atomo )
        lookahead =*buffer++; // obter_atomo();
    else{
        printf("erro sintatico: esperado [%c] encontrado [%c]\n",atomo,lookahead);
        exit(1);
    }
}
// E ::= E + F | E - F | F
// E ::= E (+|-) F | F => gramatica fatorada a esquerda
// E::= F { (+|-)F } => gramatica com eliminacao de recursividade a esquerda
void E(){
	F();
	// while garante que o trechoh {+F} ira executar zero ou mais vezes
    while( lookahead == '+' || lookahead == '-'){
        consome(lookahead);
        F();
	}

}

// F ::= num
void F(){
    if(isdigit(lookahead))
        consome(lookahead);
    else
        consome('1');
}

