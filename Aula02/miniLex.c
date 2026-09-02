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
#include <stdlib.h> // atof

// código interno atomo NUMERO
typedef enum{
    ERRO,
    NUMERO,
    IDENTIFICADOR,
    MULT, // *
    SOMA, // +
    EOS
}TAtomo;

char *strAtomo[] = {"Erro lexico", "Constante Numerica", "Identificador","*", "+","Fim de buffer"};

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
char *buffer ="  \n* ab \n \n  + 12.1   var2 ";
char lexema[20];
int contaLinha;
void reconhece_numero(TInfoAtomo *info_atomo);
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
        
        printf("%d# %s ",info_atomo.linha, strAtomo[info_atomo.atomo] );
        if( info_atomo.atomo == NUMERO )
            printf("| %f",info_atomo.atributo.numero);
        else if( info_atomo.atomo == IDENTIFICADOR )
            printf("| %s", info_atomo.atributo.ID);
        else if( info_atomo.atomo == ERRO )
            break;
        printf("\n");
        
    }

    printf("fim de programa.\n");

    return 0;
}
TInfoAtomo  obter_atomo(void){
    TInfoAtomo info_atomo;
    info_atomo.atomo = ERRO;
    // elimina espacos, faz a contagem de linhas 
    while(*buffer == ' ' || *buffer == '\n'){
        if(*buffer == '\n')
            contaLinha++; // variavel do lexico

        buffer++; 
    }

    if(*buffer == 0) // final de buffer
        info_atomo.atomo = EOS;
    else if( isdigit(*buffer)) // reconhece numero
        reconhece_numero(&info_atomo);
    else if(islower(*buffer)) // reconhece id
        reconhece_id(&info_atomo);
    else if(*buffer == '*'){
        info_atomo.atomo = MULT;
        buffer++;
    }
    else if(*buffer == '+'){
        info_atomo.atomo = SOMA;
        buffer++;
    }

    info_atomo.linha = contaLinha;
    return info_atomo;
}
/*
funcao implementa o automato para a expressao regular
DIGITO -> 0|1|...|9 
NUMERO -> DIGITO+.DIGITO+
*/
void reconhece_numero(TInfoAtomo *info_atomo){
    char *ini_lexema = buffer;
    info_atomo->atomo = ERRO;
    if(isdigit(*buffer)){
        buffer++;
        goto q1;
    }
    return;

q1:
    if( isdigit(*buffer) ){
        buffer++;
        goto q1;
    }
    if( *buffer == '.' ){
        buffer++;
        goto q2;
    }
    return;

q2:
    if( isdigit(*buffer) ){
        buffer++;
        goto q3;
    }
    return;
q3:
    if( isdigit(*buffer) ){
        buffer++;
        goto q3;
    }
    if( isalpha(*buffer)){
        return;
    }
    // recorta lexema 
    strncpy(lexema,ini_lexema,buffer-ini_lexema);
    lexema[buffer-ini_lexema] = '\0';
    info_atomo->atomo = NUMERO;
    info_atomo->atributo.numero = atof(lexema);

    return ;

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
