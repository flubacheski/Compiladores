/*
Para compilar no vscode use:
gcc miniLex.c -Wall -Og -g -o miniLex

-Wall: habilita todos avisos do compilador. Este modo indica possíveis erros cometidos no programa.
-Og: somente aplicar otimizações que não atrapalham debuging.
-g: informações para debug usando gdb
-o: output -- nome do executável gerado 
*/
#include <stdio.h>
#include <ctype.h>
#include <string.h>

// código interno atomo NUMERO
typedef enum{
    ERRO,
    NUMERO,
    IDENTIFICADOR,
    EOS
}TAtomo;

// Estrutura para comunicar com o analisador sintatico
typedef struct{
   TAtomo atomo;
   int linha;
   union{
       float numero;
       char ID[16];
   }atributo;
}TInfoAtomo;


// variavel global
char *buffer ="  \n ab \n \n  12.1   var1 var2 ";
char lexema[20];
int contaLinha;
int reconhece_numero(void);
void reconhece_id(TInfoAtomo *info_atomo);
TInfoAtomo  obter_atomo(void);

int main(){
    printf("Analisando: %s \n\n",buffer);
    TInfoAtomo info_atomo;
    info_atomo.atomo = ERRO;
    // local para o analisador lexico
    contaLinha=1;
    while( info_atomo.atomo != EOS ){
        // essa funcao sera chamada pelo analisador sintatico
        info_atomo = obter_atomo();
        
        
        if( info_atomo.atomo == NUMERO )
            printf("%d# NUMERO | %s.\n",info_atomo.linha, lexema);
        else if( info_atomo.atomo == IDENTIFICADOR )
            printf("%d# IDENTIFICADOR | %s.\n",info_atomo.linha, info_atomo.atributo.ID);
        else if( info_atomo.atomo == EOS )
             printf("%d# EOS | %s.\n",info_atomo.linha, lexema);
        else{
            printf("%d: Erro Lexico.\n",info_atomo.linha);
            break;
        }
    }

    printf("fim de programa.\n");

    return 0;
}
TInfoAtomo  obter_atomo(void){
    TInfoAtomo info_atomo;
    info_atomo.atomo = ERRO;
    // elimina espacos 
    while(*buffer == ' ' || *buffer == '\n'){
        if(*buffer == '\n')
            contaLinha++; // variavel do lexico

        buffer++; 
    }

    if(*buffer == 0)
        info_atomo.atomo = EOS;
    else if( isdigit(*buffer))
        info_atomo.atomo = reconhece_numero();
    else if(islower(*buffer))
        reconhece_id(&info_atomo);

    info_atomo.linha = contaLinha;
    return info_atomo;
}
/*
funcao implementa o automato para a expressao regular
DIGITO -> 0|1|...|9 
NUMERO -> DIGITO+.DIGITO+
*/
int reconhece_numero(void){
    char *ini_lexema = buffer;

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
    // recorta lexema 
    strncpy(lexema,ini_lexema,buffer-ini_lexema);
    lexema[buffer-ini_lexema] = '\0';

    return NUMERO;

}
// IDENTIFICADOR -> LETRA_MINUSCULA(LETRA_MINUSCULA|DIGITO)
// LETRA_MINUSCULA -> a|b|...|z
// LETRA_MAIUSCULA -> A|B|...|Z
void reconhece_id(TInfoAtomo *info_atomo){
    char *ini_lexema = buffer;
    info_atomo->atomo = ERRO;

    if( islower(*buffer)){
        buffer++;
        goto q1;
    }
    return;
q1:
    if( islower(*buffer)|| isdigit(*buffer)){
        buffer++;
        goto q1;
    }
    if( isupper(*buffer))
        return;

    // recorta lexema 
    strncpy(info_atomo->atributo.ID,ini_lexema,buffer-ini_lexema);
    info_atomo->atributo.ID[buffer-ini_lexema] = '\0';
    info_atomo->atomo = IDENTIFICADOR;
    return;
}
