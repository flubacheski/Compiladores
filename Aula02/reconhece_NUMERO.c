/*
Para compilar no vscode use:
gcc reconhece_NUMERO.c -Wall -Og -g -o reconhece_NUMERO

-Wall: habilita todos avisos do compilador. Este modo indica possíveis erros cometidos no programa.
-Og: somente aplicar otimizações que não atrapalham debuging.
-g: informações para debug usando gdb
-o: output -- nome do executável gerado 
*/
#include <stdio.h>
#include <ctype.h>
#include <string.h>

// código interno atomo NUMERO
#define ERRO 0
#define NUMERO 1

// variavel global
char *buffer ="10.2;";
char lexema[20];
int reconhece_numero();

int main(){
    printf("Analisando: %s => ",buffer);

    if( reconhece_numero() == NUMERO )
        printf("Atomo NUMERO reconhecido [%s].\n",lexema);
    else
        printf("Atomo NUMERO NAO reconhecido.\n");

    printf("fim de programa.\n");

    return 0;
}
/*
funcao implementa o automato para a expressao regular
DIGITO -> 0|1|...|9 
NUMERO -> DIGITO+.DIGITO+
*/
int reconhece_numero(){
    char *ini_lexema = buffer;
q0:
    if(isdigit(*buffer)){
        buffer++;
        goto q1;
    }
    return ERRO;

q1:
    if( isdigit(*buffer) ){
        buffer++;
        goto q1;
    }
    if( *buffer == '.' ){
        buffer++;
        goto q2;
    }
    return ERRO;

q2:
    if( isdigit(*buffer) ){
        buffer++;
        goto q3;
    }
    return ERRO;
q3:
    if( isdigit(*buffer) ){
        buffer++;
        goto q3;
    }
    if( isalpha(*buffer)){
        return ERRO;
    }
    // recorta lexama 
    strncpy(lexema,ini_lexema,buffer-ini_lexema);
    lexema[buffer-ini_lexema] = '\0';

    return NUMERO;

}
