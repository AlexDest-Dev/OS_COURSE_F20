#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    int sizeOfPyr;
    sscanf(argv[1], "%d", &sizeOfPyr);
    char pyr [sizeOfPyr][2 * sizeOfPyr - 1];
    for (int i = 0; i < sizeOfPyr; i++) {
        for (int j = 0; j < 2 * sizeOfPyr - 1; j++) {
            if (pyr[i][j] != '*') {
                pyr[i][j] = ' ';
            }
        }

        for (int j = 1; j <= i; j++) { 
            pyr[i][sizeOfPyr - 1 + j] = '*';
            pyr[i][sizeOfPyr - 1 - j] = '*';
        }
        pyr[i][sizeOfPyr-1] = '*';
    }
    for (int i = 0; i < sizeOfPyr; i++) {
        for (int j = 0; j < 2 * sizeOfPyr - 1; j++) {
            printf("%c", pyr[i][j]);
        }
        printf("\n");
    }
}
