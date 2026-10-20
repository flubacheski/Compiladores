/*
Para compilar use:
gcc -Wall -Wno-unused-result -g -Og testa_hash_mack.c hash_mack.o  -o testa_hash_mack

Para executar use:
./testa_hash_mack a b c d v1 v2 aa bb cc dd ee 

*/
#include <stdio.h>

// incluir no programa principal
int hashMack( char * s );

int main(int args,char *argv[])
{
  if (args < 2 )
  {
    printf("\nUSE:\n");
    printf("$%s  <lista de palavras>\n",argv[0]); 
    printf("\nExemplo:\n");
    printf("$%s  compiladores mackenzie v1 v2 v3 var1\n\n",argv[0]); 

    return -1; // falha na chamada do programa

  }
  for(int i=1;i<args;i++){
    int entrada = hashMack(argv[i]);
    printf("palavra [%s] entrada na tabela Hash [%d]\n",argv[i],entrada);
  }

  printf("\nfim do programa\n");
}