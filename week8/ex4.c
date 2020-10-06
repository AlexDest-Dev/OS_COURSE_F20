#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <time.h>

int main() {
    struct rusage var;
    for (int i = 0; i < 10; i++) {
        int* array = malloc(10 * 1024 * 1024 * sizeof(int));
        memset(array, 0, 10 * 1024 * 1024 * sizeof(int));
        getrusage(RUSAGE_SELF, &var);
        printf("%d\n", var.ru_maxrss);
        sleep(1);
    }
    
    
    return 0;
}
