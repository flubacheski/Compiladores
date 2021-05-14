/*
    Escreva um programa em C que remova os comentários
    (de uma linha e de várias linhas)
    de um programa fonte escrito C padrão.
    O programa fonte original deve ser lido de um arquivo,
    o seu programa terá como saída um novo arquivo fonte "limpo“,
    sem os comentários (/ * * /) e tudo que estava dentro dos comentários,
    e é claro, o programa deverá continuar compilando sem erros como antes.
*/
#include<stdio.h>//inclui printf
#include<stdlib.h> // inclui calloc

FILE  *fp_saida;
char *buffer;

char *le_arquivo(char *nome_arquivo );
void remove_comentarios(void);

int main( void )
{

    // abre o arquivo de saida
    fp_saida = fopen("saida.c","w+");
    if( !fp_saida ){
        printf("erro na abertura do arquivo de saida !");
        return 2;
    }

    buffer = le_arquivo("entrada.c");
    printf("%s",buffer);

    // chama a função
    remove_comentarios();

    // libera o buffer de leitura
    free(buffer);

    // fecha arquivo de saida
    fclose(fp_saida);

    return 0;
}
char *le_arquivo(char *nome_arquivo ){
    FILE *fp_entrada;
    char *buffer_leitura;
    long size_entrada;
    fp_entrada = fopen(nome_arquivo,"r");
    if( !fp_entrada ){
        printf("erro na abertura do arquivo de entrada !");
        exit(1);
    }

    /* calcula o tamanho em bytes do arquivo de entrada * / */
    fseek (fp_entrada, 0, SEEK_END); // move o ponteiro do arquivo para o final
    size_entrada=ftell(fp_entrada); // obtem a quantidade de bytes deslocados
    fseek (fp_entrada, 0, SEEK_SET); //move o ponteiro do arquivo para o inicio

    // aloca um buffer para ler o arquivo de entrada
    buffer_leitura = (char*)calloc(size_entrada,sizeof(char));

    //le o arquivo de entrada
    fread (buffer_leitura,sizeof(char),size_entrada,fp_entrada);

    // fecha arquivo de entrada
    fclose(fp_entrada);
    return buffer_leitura;
}
void remove_comentarios(){
r0:
    if( *buffer == '/'){
        buffer++;
        goto r1;
    }
    if( *buffer != '\x0'){ // outro
        // grava e anda no buffer
        fprintf(fp_saida,"%c",*buffer++);
        goto r0;
    }
    // sai da funcao
    return ;
r1:
    if( *buffer == '*'){
        buffer++;
        goto r2;
    }
    if( *buffer != '\x0'){ // outro
        // grava e anda no buffer
        fprintf(fp_saida,"/");
        goto r0;
    }
    // sai da funcao
    return ;
r2:
    if( *buffer == '*'){
        buffer++;
        goto r3;
    }
    if( *buffer != '\x0'){ // outro
        // anda o buffer
        buffer++;
        goto r2;
    }
    return ;

r3:
    if( *buffer == '/'){
        buffer++;
        goto r0;
    }
    if( *buffer != '\x0'){ // outro
        // anda o buffer
        buffer++;
        goto r2;
    }
    return;
}
