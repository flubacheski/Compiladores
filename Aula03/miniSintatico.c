/*
Integracao entre Lexico e Sintatico

Para compilar no vscode use:

gcc miniLex.c miniSintatico.c -Wall -Og -g -o compilador

-Wall: habilita todos avisos do compilador. Este modo indica possíveis erros cometidos no programa.
-Og: somente aplicar otimizações que não atrapalham debuging.
-g: informações para debug usando gdb
-o: output -- nome do executável gerado 

Para criar um arquivo de Makefile acesse:
https://diveintosystems.org/book/Appendix2/makefiles.html#_make_and_makefiles
*/

#include <stdio.h>
#include <stdlib.h>
#include "miniLex.h"

// varivel global declarada no miniLex.c
extern char *strAtomo[];

// variavel global do analisador sintatico
TAtomo lookahead;
TInfoAtomo info_atomo;


// E :: = numero | identificador | +EE |*EE
void E(); // prototipacao de funcao
void consome( TAtomo atomo );

int main(){
    // primeira chamada para inicializar o lookahead
    info_atomo = obter_atomo();
    lookahead = info_atomo.atomo;
    
    E(); // chama o simbolo inicial da gramatica

    consome(EOS);

    printf("Compilador\nAnalise sintatica concluida sem erros\n");

    return 0;
}
void consome( TAtomo atomo ){
    if( lookahead == atomo ){
        info_atomo = obter_atomo();
        lookahead = info_atomo.atomo;
    }
    else{
        // tratador de erros
        printf("Erro sintatico: esperado [%s] encontrado [%s]\n",strAtomo[atomo],strAtomo[lookahead]);
        exit(1);
    }
}

// E :: = numero | identificador | +EE |*EE
void E(){
    switch( lookahead ){
        case SOMA:
            consome(SOMA);
            E();E();
            break;
        case MULT:
            consome(MULT);
            E();E();
            break;
        case IDENTIFICADOR:
            consome(IDENTIFICADOR);
            break;
        default:
            consome(NUMERO);

    }


}
