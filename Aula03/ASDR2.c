/*
Primeira versao do analisador sintatico.

gcc ASDR2.c -o ASDR2
*/

#include <stdio.h>
#include <stdlib.h>

// variavel global do analisador lexico
char *buffer ="+ac";

// variavel global do analisador sintatico
char lookahead;

// E ::= a | b | +EE | *EE
void E(); // prototipacao de funcao
void consome( char atomo );

int main(){
    printf("Analisando: %s => ",buffer);
    lookahead = *buffer++; //obter_átomo
    E(); // chama o simbolo inicial da gramatica

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

// E ::= a | b | +EE | *EE
void E(){
    switch( lookahead ){
        case '+':
            consome('+');
            E();E();
            break;
        case '*':
            consome('*');
            E();E();
            break;
        case 'a':
            consome('a');
            break;
        default:
            consome('b');

    }


}
