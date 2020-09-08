#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main() {
    char input_command[100];
    printf("Shell:\nexit - command for exit from shell:\n");
    while(strcmp(input_command, "exit") != 0) {
        scanf("%s", &input_command);
        system(input_command);
    }
    return 0;
}


