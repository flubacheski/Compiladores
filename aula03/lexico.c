#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Definicao de uma estrutura enumeracao para as constantes dos atomos (Tokens)
typedef enum{
	ERRO,
    IDENTIFICADOR,
    NUMERO_INTEIRO,
    ATRIBUICAO,
    WHILE,
    EOS
}TAtomo;


// definicao de uma estrutura union para os atributos do atomo (Tokens)
typedef union
{
	char str_id[17];//16+1 para guardar o \0
	int valor_inteiro;
	float valor_real;
}TAtributo;

// definição de uma estrutura para retornar as informações do atomo
// Atomo (token), numero da linha e atributo
typedef struct{
  TAtomo atomo; //Constante representando o átomo
  int linha; //Número da linha onde o átomo foi encontrado
  int atributo_numero;
  char atributo_ID[15];
}TInfoAtomo;

// Mensagens do compilador indexadas pelos atomos (tokens)
char *msg_atomo[]={
		"Erro Lexico",
		"Identificador",
		"Numero Inteiro",
		"Atribuicao",
		"While"
		"Fim de Buffer"};


// funcao principal do analisador lexico, retorna o atomo reconhecido
// com seus atributos
TInfoAtomo obter_atomo(void);

// variaveis globais
char *buffer="\n\n\n     fabio \nlubacheski \n123.1";
int linha=1;

int main( void )
{
	TInfoAtomo info_atomo;

    // abrir arquivo
    // alocar o buffer_global em funcao do tamanho do arquivo de entrada

	printf("Analisador Lexico versao 1.0\n");

	do{
		info_atomo = AnaLex();
		printf("[%d]reconhecido %s - atributo=%s\n", linha,msg_atomo[info_atomo.atomo], info_atomo.atributo.str_id);
	}while( info_atomo.atomo != EOS && info_atomo.atomo != ERRO );
    return 0;
}
/*
 Reconhece um IDENTIFICADOR
*/
void reconhece_id(TInfoAtomo *infoAtomo){

    int i=0;

    // q0
    infoAtomo->atributo_ID[i++] = *buffer++;
    // q1
    while(isalpha(*buffer) || isdigit(*buffer))
        infoAtomo->atributo_ID[i++]=*buffer++;


    // q2
    // finaliza o lexema
    infoAtomo->atributo_ID[i++]=0;

    // verifica se o lexama
    infoAtomo->atomo = IDENTIFICADOR;

/*
 Reconhece um NUMERO INTEIRO E NUMERO REAL
*/
TAtomo reconhece_num(void)
{

	return ERRO;
}
/*
 funcao principal do analisador lexico, retorna o atomo reconhecido
 com seus atributos
*/
TInfoAtomo obter_atomo(void)
{
	char c;
	TInfoAtomo info_atomo;

    // limpa a estrutura  seta info_atomo com ERRO
	memset(&info_atomo,0,sizeof(info_atomo));

	// trata os caracteres de controle
	while( *buffer==' ' || *buffer=='\n' || *buffer=='\r' ){
		if(*buffer=='\n')
			linha++;

		buffer++;
	}
	info_atomo.linha = linha;


	if(isalpha(*buffer)){//[A-Za-z]
		reconhece_id(&info_atomo);
	}
	else if(isdigit(c)){ // [0-9]
		info_atomo.atomo = reconhece_num();
	}
	else if( c == '\0' )
    	info_atomo.atomo = EOS;

	return info_atomo;
}
