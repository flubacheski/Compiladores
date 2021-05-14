/*
Constroi um ASDR para gramatica abaixo
E ::= a | b | +EE | *EE
*/
#include <stdio.h>
#include <stdlib.h>

char *buffer="*+abba";
void E();

int main(void){
    printf("analisando %s\n",buffer);
    E();
    if( *buffer == '\x0')// fim de buffer
        printf("palavra aceita.");
    else
        printf("\nerro sintatico 2.");

    printf("\nfim de programa.\n");
    return 0;
}
// funcao para producao
// E ::= a | b | +EE | *EE
void E(){
    switch(*buffer){
        case '+':
            buffer++; // consome +
            E();E();
            break;
        case '*':
            buffer++; // consome *
            E();E();
            break;
        case 'a':
        case 'b':
            buffer++; // consome a ou b
            break;
        default:
            printf("\nerro sintatico 1.");
            exit(1);


    }

}
