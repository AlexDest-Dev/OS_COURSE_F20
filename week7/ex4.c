#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

void * reallocation(void* ptr, size_t size) {
    if (ptr == NULL) {
        ptr = malloc(size);
        return ptr;
    }
    if (size == 0) {
        free(ptr);
        return ptr;
    }
    void* newptr = malloc(size);
    memcpy(newptr, ptr, size);
    return newptr;
}

int main() {
    int n = 5;
    int* array = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        array[i] = i + 1;
        printf("%d ", array[i]);
    }
    int m = 10;
    array = reallocation(array, m * sizeof(int));
    printf("\n");
    for (int i = 0; i < m; i++) {
        printf("%d ", array[i]);
    }
    for (int i = n; i < m; i++) {
        array[i] = i + 1;
    }
    printf("\n");
    for (int i = 0; i < m; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
    return 0;
}
