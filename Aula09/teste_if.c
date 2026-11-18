#include <stdio.h>

int main(){

    int a=10;
    int b=5;
    int c=7;

    if( a > b )
        if( b > c )
            printf("a");
    else
        printf("b");
    
    printf("fim");
}