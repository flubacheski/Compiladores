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

char *buffer;
FILE *fp_entrada, *fp_saida;

void remove_comentarios(void);

int main( void )
{
    long size_entrada;
    fp_entrada = fopen("entrada.c","r");
    if( !fp_entrada ){
        printf("erro na abertura do arquivo de entrada !");
        return 1;
    }
    fp_saida = fopen("saida.c","w+");
    if( !fp_saida ){
        printf("erro na abertura do arquivo de saida !");
        return 2;
    }
    /* calcula o tamanho em bytes do arquivo de entrada * / */
    fseek (fp_entrada, 0, SEEK_END); // move o ponteiro do arquivo para o final
    size_entrada=ftell(fp_entrada); // obtem a quantidade de bytes deslocados
    fseek (fp_entrada, 0, SEEK_SET); //move o ponteiro do arquivo para o inicio

    // aloca um buffer para ler o arquivo de entrada
    buffer = (char*)calloc(size_entrada,sizeof(char));

    //le o arquivo de entrada
    fread (buffer,sizeof(char),size_entrada,fp_entrada);
    printf("%s",buffer);

    // chama a função
    remove_comentarios();

    // libera o buffer de leitura
    free(buffer);

    // fecha os arquivos
    fclose(fp_entrada);
    fclose(fp_saida);

    return 0;
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
