/*
Primeira versao do analisador sintatico.

*/

#include <stdio.h>
#include <stdlib.h>

// variavel global
char *buffer ="+abc";
// E ::= a | b | +EE | *EE
void E(); // prototipacao de funcao

int main(){
    printf("Analisando: %s => ",buffer);

    E(); // chama o simbolo inicial da gramatica
    if(*buffer == '\x0')//testa se chegar ao final do buffer
        printf("\nsintaxe correta.\n");
    else
        printf("\nErro sintatico, nao cheguei ao final do buffer.\n");

    printf("fim de programa.");

    return 0;
}
// E ::= a | b | +EE | *EE
void E(){
    switch( *buffer ){
        case '+':
            //consome +
            buffer++;
            E();E();
            break;
        case '*':
            //consome *
            buffer++;
            E();E();
            break;
        case 'a':
            //consome a
            buffer++;
            break;
        case 'b':
            //consome a
            buffer++;
            break;
        default:
            printf("\nErro sintatico, preciso de dois operandos.\n");
            exit(1);
    }


}
