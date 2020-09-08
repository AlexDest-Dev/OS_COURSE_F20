#include <stdio.h>
#include <unistd.h>

int main() {
    int n = fork();
    char* name_of_process;
    if (n == 0) name_of_process = "child";
    else name_of_process = "parent";
    printf("Hello from %s [%d - %d]\n", name_of_process, getpid(), n);
    return 0;
}
