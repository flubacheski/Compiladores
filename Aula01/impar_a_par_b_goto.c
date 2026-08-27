/*
Links importante para entender o código
https://www.ime.usp.br/~pf/algoritmos/aulas/pont.html
https://wiki.inf.ufpr.br/maziero/doku.php?id=c:ponteiros
*/
#include <stdio.h>
#include <string.h>
// declaracao da funcao
int Impar_a_Par_b(char*entrada);

int main ()
{
    char*entrada="aabb";
    printf("reposta:%d",Impar_a_Par_b(entrada));
}

// implementacao da funcao
// retorna 1 se quantidade a´s for impar e de b´s for par
// 0 caso contrario
int Impar_a_Par_b(char*entrada)
{
PaPb:
    if(*entrada == 'a'){
        entrada++;// consome a
        goto IaPb;// vai para o proximo estado
    }
    if(*entrada == 'b'){
        entrada++;// consome b
        goto PaIb;// vai para o proximo estado
    }
    // final da palavra
    return 0;
IaPb:
    if(*entrada == 'a'){
        entrada++;// consome a
        goto PaPb;// vai para o proximo estado
    }
    if(*entrada == 'b'){
        entrada++;// consome b
        goto IaIb;// vai para o proximo estado
    }
    return 1;
PaIb:
    if(*entrada == 'a'){
        entrada++;// consome a
        goto IaIb;// vai para o proximo estado
    }
    if(*entrada == 'b'){
        entrada++;// consome b
        goto PaPb;// vai para o proximo estado
    }
    // final da palavra
    return 0;
IaIb:
    if(*entrada == 'a'){
        entrada++;// consome a
        goto PaIb;// vai para o proximo estado
    }
    if(*entrada == 'b'){
        entrada++;// consome b
        goto IaPb;// vai para o proximo estado
    }
    // final da palavra
    return 0;

}