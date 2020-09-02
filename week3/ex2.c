#include <stdio.h>

void bubble_sort(int arrSize, int array[]) {
    for (int i = 0; i < arrSize; i++) {
        for (int j = i + 1; j < arrSize; j++) {
            if (array[i] > array[j]) {
                int t = array[i];
                array[i] = array[j];
                array[j] = t;
            }
        }
    }
}

int main() {
    int arrSize;
    printf("Write a size of array:\n");
    scanf("%d", &arrSize);

    int array[arrSize];
    printf("Write numbers through a space:\n");
    for (int i = 0; i < arrSize; i++) {
        scanf("%d", &array[i]);
    }
    
    bubble_sort(arrSize, &array);
    for (int i = 0; i < arrSize; i++) {
        printf("%d ", array[i]);
    }
    return 0;
}
