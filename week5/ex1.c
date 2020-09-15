#include <stdio.h>
#include <pthread.h>
// In first variant, threads start one after another and finish in reverse order
void thread_show(int id) {
    int thread_id = id;
    printf("Thread #%d is finished\n", thread_id);
}
int main() {
    printf("Write number of threads: \n");
    int threads_number;
    scanf("%d", &threads_number);
    pthread_t thr_id = 1;
    for (int i = 0; i < threads_number; i++) {
        printf("Thread #%d is created\n", i, (int)thr_id);  
        pthread_create(&thr_id, NULL, &thread_show, i);
        pthread_join(thr_id, NULL);
    }
    pthread_exit(NULL);
    return 0;
}
