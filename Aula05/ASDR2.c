/*
Constroi um ASDR para gramatica abaixo
E ::= a | b | +EE | *EE
utilizando uma variável (lookahead) para armazenar o símbolo
a ser analizado (Left most)
E uma unica funcao que mais adianta fara a integracao
com o Analisador Lexico.
*/
#include <stdio.h>
#include <stdlib.h>

char *buffer="*+abb";
char lookahead;
void E();
void consome( char atomo );

int main(void){
    printf("analisando %s\n",buffer);
    // antes de comecar a analise atualiza lookahead
    lookahead = *buffer++;// lookahead = get_atomo()
    E();
    if( lookahead == '\x0')// fim de buffer (EOS)
        printf("palavra aceita.");
    else
        printf("\nerro sintatico 2.");

    printf("\nfim de programa.\n");
    return 0;
}
// funcao para producao
// E ::= a | b | +EE | *EE
void E(){
    switch(lookahead){
        case '+':
            consome('+');
            E();E();
            break;
        case '*':
            consome('*');
            E();E();
            break;
        case 'a':
        case 'b':
            consome(lookahead);
            break;
        default:
            printf("\nerro sintatico 1.");
            exit(1);


    }

}
/*
Essa funcao sera a unica que fara chamados
ao analisador lexico.
funcao atualiza a variavel lookahead e verifica
se o simbolo mais a esquerda casa com o simbolo
esperado, caso nao case temos um erro sintatico
*/
void consome( char atomo ){
    if( lookahead == atomo )
        lookahead =*buffer++; // obter_atomo();
    else{
        printf("erro sintatico: esperado [%c] encontrado [%c]\n",atomo,lookahead);
        exit(1);
    }
}

