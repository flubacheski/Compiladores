// links para funcoes que vamos utilizar
// http://www.cplusplus.com/reference/cstring/strncpy/
// https://en.wikibooks.org/wiki/C_Programming/C_Reference/nonstandard/strcasecmp
#include <stdio.h>
#include <stdlib.h>

char *buffer; // buffer lido
char *iniBuffer; // guarda o inicio do buffer para desalocar

// constantes para os atomos do mini analisador léxico
typedef enum{
    ERRO,
    IDENTIFICADOR,
    NUMERO_INTEIRO,
    ATRIBUICAO,
    WHILE,
    EOS
}TAtomo;

// estrutura para retornar as informações de um atomo (tokens)
typedef struct{
    TAtomo atomo;
    int linha;
    int atributo_numero;
    char atributo_ID[15];
}TInfoAtomo;

TInfoAtomo obter_atomo();

int main(void){
    FILE *fp_entrada;
    TInfoAtomo infoAtomo;

    // abre o arquivo
    fp_entrada = fopen("teste.pas", "r");
    if(!fp_entrada){ // testa se abriu corretamente
        printf("erro na abertura do arquivo de entrada.\n");
        return 1;
    }
    // abertura e leitura de arquivo
    fseek(fp_entrada, 0, SEEK_END); // move ponteiro do arquivo para o final
    long tamanho = ftell(fp_entrada); // conta a quantidade de bytes deslocados na movimentacao
    fseek(fp_entrada, 0, SEEK_SET); // move novamente para o inicio do arquivo
    buffer = (char*)calloc(tamanho+1,sizeof(char)); // aloca os memoria para guardar o arquivo lido
    fread(buffer, sizeof(char),tamanho,fp_entrada); // le de uma vez so o arquivo
    fclose(fp_entrada); // fecha arquivo

    printf("%s",buffer);


    infoAtomo = obter_atomo();

    free(iniBuffer);
    return 0;
}
/*
A rotina obter_atomo() do mini analisador léxico retorna para cada átomo reconhecido uma codificação inteira (constante) para representar o
valor do átomo e o seu atributo, caso se faça necessário para o átomo.
*/
TInfoAtomo obter_atomo(){
    TInfoAtomo infoAtomo;

    infoAtomo.atomo = ERRO;

    return infoAtomo;

}
