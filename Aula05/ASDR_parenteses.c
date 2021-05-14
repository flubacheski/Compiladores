/*
Implementação do ASDR para a gramatica
    S ::= E S | vazio
    E ::= ( S ) | [ S ] | vazio



*/
#include <stdio.h>
#include <stdlib.h> // exit

// palavra a ser analisada declara globalmente
char *palavra = "(()[]()[]()[])";
void S();
void E();

int main(){
    printf("entrada : %s\n", palavra);

    S();
    // verificar se o ASDR chegou ao final da palavra
    if( *palavra == '\0')
        printf("\n\npalavra pertence a linguagem.\n");
    else
        printf("\n\nerro sintatico, esperado fim de string encontrado %c \n", *palavra);
    return 0;
}
// funcao representa o nao-terminal S
// S ::= E S | vazio
void S(){
    if( *palavra == '(' || *palavra == '['){
        E();
        S();
    }
}

// funcao representa o nao-terminal E
// E ::= ( S ) | [ S ] | vazio
void E(){

    if( *palavra == '(' ){
       palavra++; // consome o '('
       S();
       if(*palavra==')')
            palavra++; // consome o ')'
       else{
            printf("\n\nerro sintatico, esperado fim de string encontrado %c \n", *palavra);
            exit(1);
       }
    }
    else if( *palavra == '[' ){
       palavra++; // consome o '['
       S();
       if(*palavra==']')
            palavra++; // consome o ']'
       else{
            printf("\n\nerro sintatico, esperado fim de string encontrado %c \n", *palavra);
            exit(1);
       }
    }

}
