/*
Etapa 1. PRÉ-PROCESSADOR
gcc -E olamundo.c ou gcc -S olamundo.c
substitui o #define's,código, resolve o #include's e remove os comentários

Etapa 2. COMPILAÇÃO:
gcc -c olamundo.c

Ele gera o arquivo objeto olamundo.o, que contém basicamente:
1. Alocação dos segmentos de código, pilha e BSS em código relocável.
2. Desconstrução em assembly do código de alto nível de test.c.
3. Tabela de símbolos.

use objdump -x olamundo.o para apresentar o arquivo objeto (.o)

Etapa 3. LINKER:
Util quando você usa vários arquivos .o com o linker vc pode juntar
gcc olamundo.o -o olamundo

Agora temos  um executavel, basta chamar o carregador do SO (loader) 
./olamundo

*/
#include <stdio.h>

#define HELLOWORLD "Ola Mundo\n"
int main (int argc, char *args[])
{
   printf(HELLOWORLD);
   return 0;
}
