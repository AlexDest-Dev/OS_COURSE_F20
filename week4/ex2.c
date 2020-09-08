#include <stdio.h>
#include <unistd.h>

int main() {
    int number_forks = 5;
    for (int i = 0; i < number_forks; i++) {
        fork();
        sleep(5);
    }

    return 0;
}
