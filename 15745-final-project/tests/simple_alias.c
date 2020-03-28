#include <stdio.h>
#include <stdlib.h>
int main(){
    int k = 0x50;
    int j = 2;

    int *x = &k;
    int *y = x;
    int *z = &j; 
    printf("x = %p, y = %p, z = %p\n", x, y, z);
    return k + j;
}
