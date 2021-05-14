/*

  Analisador lexico (baseado no automato) que reconhece palavras
  que representam números inteiros em uma linguagem de programação.

*/
#include<stdio.h>//inclui printf

// Para implementar o analisador lexico considere que a cadeia a ser analisada
// esta armazenada na variavel *cadeia declarada globalmente e ja lida.
char *cadeia = "1*";

int AnaLex(void);

int main( void )
{
    char *iniCadeia = cadeia;
    if( AnaLex() )
        printf("[%s] - Palavra aceita ", iniCadeia);
    else
        printf("[%s] - Palavra NAO aceita ", iniCadeia);



}
// funcao retorna 1 caso a cadeia faca parte da linguagem
// ou 0 caso contrario
int AnaLex(void){

r0: // estado inicial
    if( *cadeia == '+' || *cadeia == '-'){
        cadeia++;
        goto r1;
    }
    if( isdigit(*cadeia)){
        cadeia++;
        goto r2;
    }
    // caso não seja + ou - ou digito retorna 0 (nao)
    return 0;
r1:
    if( isdigit(*cadeia)){
        cadeia++;
        goto r2;
    }
    // caso não seja digito retorna 0 (nao)
    return 0;

r2: // estado final

    if( isdigit(*cadeia)){
        cadeia++;
        goto r2;
    }
    // caso não seja digito retorna e tenha chegado ao final da palavra retorna 1 (sim)
    return *cadeia == '\x0';
}
