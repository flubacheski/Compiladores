#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
/*
ASDR para gramatica
	S ::= AS | BA
	A ::= aB | C
	B ::= bA | d
	C ::= c

FIRST(C)={c}
FIRST(A)= {a,FIRST(C)}={a,c}
FIRST(B)={b,d}
FIRST(S)={FIRST(A),FIRST(B)}={a,b,c,d}

*/

//char *buffer="abaddc";
char *buffer="ca";// nao aceita essa palavra
char lookahead; // simbolo no inicio da cadeia
void consome( char atomo );
void S();
void A();
void B();
void C();

int main(void){
    printf("analisando %s\n",buffer);
    //inicializa a variavel global com o primeiro simbolo no inicio do buffer.
    //e anda com o buffer, ou seja, atualiza uma posicao pra frente o buffer
    lookahead = *buffer++;
    S();
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
// S ::= AS | BA
// FIRST(A)= {a,FIRST(C)}={a,c}
// FIRST(B)={b,d}
void S(){
    if( lookahead == 'a' || lookahead == 'c'){
        A();S();
    }else{
        B();A();
    }

}
// A ::= aB | C
void A(){
    if( lookahead == 'a' ){
        consome('a');
        B();
    }
    else
        C();

}
// B ::= bA | d
void B(){
    if( lookahead == 'b'){
        consome('b');
        A();
    }
    else
        consome('d');

}

// C ::= c
void C(){
    consome('c');
}

