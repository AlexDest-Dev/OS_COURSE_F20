#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 1024
int main() {
    char *userString = malloc(MAX_LEN);
    fgets(userString, MAX_LEN, stdin);
    int stringLength = strlen(userString);
    for (int i = stringLength - 1; i >= 0; i--) {
        printf("%c", *(userString + i));
    }
    printf("\n");
    return 0;
}
