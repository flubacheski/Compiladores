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

// Estrutura para comunicar com o analisador sintatico
typedef struct{
   TAtomo atomo;
   int linha;
   union{
       float numero;
       char ID[16];
   }atributo;
}TInfoAtomo;



// declaracao de funcao
void reconhece_numero(TInfoAtomo *info_atomo);
void reconhece_id(TInfoAtomo *info_atomo);
TInfoAtomo  obter_atomo(void);