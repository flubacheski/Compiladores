#include <ctype.h> // isdigit e isalpha
#include <string.h> // strncpy
#include <stdio.h>
#include <stdlib.h>

char *buffer; // buffer lido
char *iniBuffer; // guarda o inicio do buffer para desalocar
int contaLinha=1; // faz a contagem global de linhas
// constantes para os atomos do mini analisador léxico
typedef enum{
    ERRO,
    IDENTIFICADOR,
    NUMERO_INTEIRO,
    ATRIBUICAO,
    WHILE,
    EOS
}TAtomo;

// mensagens referentes aos atomos para impressao
char *StrAtomo[]={
    "ERRO LEXICO",
    "IDENTIFICADOR",
    "NUMERO_INTEIRO",
    "ATRIBUICAO",
    "WHILE",
    "FIM DE BUFFER"
};
// estrutura para retornar as informações de um atomo (tokens)
typedef struct{
    TAtomo atomo;
    int linha;
    int atributo_numero;
    char atributo_ID[15];
}TInfoAtomo;

TInfoAtomo obter_atomo();
void reconhece_num(TInfoAtomo *infoAtomo);
void reconhece_ID(TInfoAtomo *infoAtomo);

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

    //printf("%s",buffer);
    printf("Inicio da analise lexica.\n");
    while( 1 ) {
        infoAtomo = obter_atomo();
        printf("\nlinha:%d | %s ",infoAtomo.linha, StrAtomo[infoAtomo.atomo]);
        if( infoAtomo.atomo == NUMERO_INTEIRO )
            printf("| %d",infoAtomo.atributo_numero);
        if( infoAtomo.atomo == IDENTIFICADOR )
            printf("| %s",infoAtomo.atributo_ID);
        if( infoAtomo.atomo == EOS || infoAtomo.atomo == ERRO)
            break;
    }
    printf("\nfim de analise lexica do arquivo.\n");
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
    while(*buffer==' '||*buffer == '\t'||*buffer == '\r'|| *buffer == '\n' ){
        if(*buffer == '\n')
            contaLinha++;
        buffer++;
    }
    infoAtomo.linha = contaLinha;

    if(*buffer == ':' && *(buffer+1) == '='){
        buffer+=2;
        infoAtomo.atomo = ATRIBUICAO;
    }
    else if(isdigit(*buffer)){
        reconhece_num(&infoAtomo);
    }
    else if(isalpha(*buffer)){
        reconhece_ID(&infoAtomo);
    }
    else if(*buffer == 0)
        infoAtomo.atomo = EOS;

    return infoAtomo;

}
void reconhece_num(TInfoAtomo *infoAtomo){
    char *ini_num = buffer;

    while( isdigit(*buffer))
        buffer++;

    if(isalpha(*buffer) ) // erro
        return;
    // http://www.cplusplus.com/reference/cstring/strncpy/
    strncpy(infoAtomo->atributo_ID,ini_num, buffer-ini_num);
    infoAtomo->atributo_ID[buffer-ini_num]=0;
    //converte para inteiro o atributo
    infoAtomo->atributo_numero = atoi(infoAtomo->atributo_ID);
    infoAtomo->atomo = NUMERO_INTEIRO;
}
void reconhece_ID(TInfoAtomo *infoAtomo){

    char *ini_num = buffer;

    while( isdigit(*buffer) || isalpha(*buffer))
        buffer++;
    // http://www.cplusplus.com/reference/cstring/strncpy/
    strncpy(infoAtomo->atributo_ID,ini_num, buffer-ini_num);
    infoAtomo->atributo_ID[buffer-ini_num]=0;
    infoAtomo->atomo = IDENTIFICADOR;

    //verifica se ID eh palavra reservada
    //https://en.wikibooks.org/wiki/C_Programming/C_Reference/nonstandard/strcasecmp
    if( strcasecmp(infoAtomo->atributo_ID,"WHILE")==0)
            infoAtomo->atomo = WHILE;

}
