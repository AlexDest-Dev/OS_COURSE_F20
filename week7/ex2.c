#include <stdio.h>
#include <stdlib.h>
int main() {
    int N;
    printf("Write size of an array:\n");
    scanf("%d", &N);
    int* array = malloc(N*sizeof(int));
    for (int i = 0; i < N; i++) {
        array[i] = i;
    }
    
    for (int i = 0; i < N; i++) {
        printf("%d ", array[i]);   
    }
    printf("\n");
    free(array);
}
