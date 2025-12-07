#include <stdio.h>
#include <time.h>

int main(){
    clock_t start = clock();
    int i;
    for(int t = 0; t <= 1000000; t++){
        i = 4 + 7;
    }
    clock_t end = clock();
    double elapsed = (double)(end-start) / CLOCKS_PER_SEC;

    printf("%f", elapsed);
}