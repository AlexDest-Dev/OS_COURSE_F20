#include <stdio.h>
void swap(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
}
int main() {
    int a, b;
    scanf("%d %d", &a, &b, stdin);
    swap(&a, &b);
    printf("a = %d\nb = %d\n", a, b);
    return 0;
}
