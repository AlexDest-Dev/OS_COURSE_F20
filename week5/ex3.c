#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <pthread.h>

// Data for buffer
int buffer_size = 10;
int current_size = -1;
int *buffer;
// Bool variable for determining of state of threads
bool consumer_sleep = true;
bool producer_sleep = false;
// Variable for stopping of application
bool app_pause = false;
// Variable for termnating of application
bool app_active = true;

int changes_counter = 0;
const int max_changes = 100000;

//Function for output of buffer
void output_buffer() {
    printf("\n");
    for (int i = 0; i < buffer_size; i++) {
        printf("%d ", buffer[i]);
    }
    printf("\n");
}
// Function, which change last number on -1 (consume data)
void* consumer_actions() {
    printf("Consumer is started!\n");
    // Flag for checking, that application was stopped
    bool thread_stop = false;
    while(app_active) {
        while (!app_pause) {
            if (changes_counter > max_changes) {
                output_buffer();
                changes_counter = 0;
            }
            // Cycle of waiting for possibility of making action
            while (consumer_sleep) {
                if (app_pause) {
                    thread_stop = true;
                    break;
                }
            }
            if (thread_stop) break;
            // Consuming of information
            if (current_size < 0) {
                consumer_sleep = true;
            } else {
                producer_sleep = true;
                buffer[current_size] = -1;
                current_size--;
                changes_counter++;
                producer_sleep = false;
            }
        }
    }
    printf("Consumer is done!\n");
    pthread_exit(NULL);
}
// Function, which change first input of -1 on 1 (produce data)
void* producer_actions() {
    printf("Producer is started!\n");
    // Flag for checking, that application was stopped
    bool thread_stop = false;
    while (app_active) {
        
        while (!app_pause) {
            if (changes_counter > max_changes) {
                output_buffer();
                changes_counter = 0;
            }
            // Cycle of waiting for possibility of making action
            while (producer_sleep) {
                if (app_pause) {
                    thread_stop = true;
                    break;
                }
            }
            if (thread_stop) break;
            // Producing of information
            if (current_size >= buffer_size) {
                producer_sleep = true;
            } else {
                consumer_sleep = true;
                current_size++;
                buffer[current_size] = 1;
                changes_counter++;
                consumer_sleep = false;
            }
        }
    }
    printf("Producer is done!\n");
    pthread_exit(NULL);
}

int main() {
    // Input and output information for control and configuration of app
    printf("Please, write size for buffer of information( array of integers:\n");
    scanf("%d", &buffer_size);
    int temp_array[buffer_size];
    buffer = temp_array;
    for (int i = 0; i < buffer_size; i++) {
        buffer[i] = -1;
    }
    printf("Manual:\ns - terminate app\np - pause app\nc - continue after pause\no - output current buffer\nIf you want start, send y:\n");
    char command;
    scanf("%c", &command);
    while (command != 'y') {
        printf("Please, if you want start, than send y:\n");
        scanf("%c", &command);
    }
    // Start threads
    pthread_t producer_thread;
    pthread_t consumer_thread;
    pthread_create(&producer_thread, NULL, &producer_actions, NULL);
    pthread_create(&consumer_thread, NULL, &consumer_actions, NULL);
    // Checking of command line
    while (true) {
        scanf(" %c", &command);
        if (command == 'p') {
            app_pause = true;
        }
        if (command == 'c') {
            app_pause = false;
        }
        if (command == 's') {
            app_pause = true;
            app_active = false;
            break;
        }
        if (command == 'o') {
            output_buffer();
        }
    }
    pthread_exit(NULL);
    return 0;
}
