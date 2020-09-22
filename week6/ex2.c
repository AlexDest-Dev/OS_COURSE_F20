#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
struct process {
    int number;
    int arrival_time;
    int burst_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
    bool used;
};

int compare_processes(struct process A, struct process B) {
    if (A.arrival_time > B.arrival_time) {
        return 1;
    }
    else if (A.arrival_time < B.arrival_time) {
        return -1;
    }
    else {
        return 0;
    }
}
void AT_sort_processes(struct process* processes, int processes_number) {
    for (int i = 0; i < processes_number; i++) {
        for (int j = i + 1; j < processes_number; j++) {
            if (compare_processes(*(processes + i), *(processes + j)) > 0) {
                struct process temp = *(processes + i);
                *(processes + i) = *(processes + j);
                *(processes + j) = temp;
            }
        }
    }
}

int main() {
    int processes_number;
    printf("Enter number of processes:\n");
    scanf("%d", &processes_number);
    printf("Enter Arrival Time and Burst Time for each process:\n");
    struct process* processes = malloc(processes_number * sizeof(struct process));
    for (int i = 0; i < processes_number; i++) {
        int temp_AT, temp_BT;
        printf("Arrival Time of Process [%d]:\n", i + 1);
        scanf("%d", &temp_AT);
        printf("Burst Time of Process [%d]:\n", i + 1);
        scanf("%d", &temp_BT);
        processes[i].arrival_time = temp_AT;
        processes[i].burst_time = temp_BT;
        processes[i].number = i + 1;
        processes[i].used = false;
    }
    AT_sort_processes(processes, processes_number);
    int current_time = 0;
    while (true) {
        bool all_processes_used = true;
        int index_of_current_process = -1;
        int min_BT = INT32_MAX;
        for (int j = 0; j < processes_number; j++) {
            if (!processes[j].used && processes[j].arrival_time <= current_time && processes[j].burst_time < min_BT) {
                min_BT = processes[j].burst_time;
                index_of_current_process = j;
            }
        }
        if (index_of_current_process < 0) {
            current_time++;
            continue;
        }
        processes[index_of_current_process].completion_time = current_time + processes[index_of_current_process].burst_time;
        processes[index_of_current_process].turnaround_time = processes[index_of_current_process].completion_time - processes[index_of_current_process].arrival_time;
        processes[index_of_current_process].waiting_time = processes[index_of_current_process].turnaround_time - processes[index_of_current_process].burst_time;
        processes[index_of_current_process].used = true;
        current_time = processes[index_of_current_process].completion_time;
        for (int i = 0; i < processes_number; i++) {
            if (!processes[i].used) all_processes_used = false;
        }
        if (all_processes_used) break;
    }

    float average_TAT = 0;
    float average_WT = 0;
    for (int i = 0; i < processes_number; i++) {
        average_TAT += (float)processes[i].turnaround_time;
        average_WT += (float)processes[i].waiting_time;
    }
    average_TAT /= processes_number;
    average_WT /= processes_number;
    printf("P#\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < processes_number; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", processes[i].number, processes[i].arrival_time,
               processes[i].burst_time, processes[i].completion_time, processes[i].turnaround_time, processes[i].waiting_time);
    }
    printf("Average Turnaround Time = %f\n", average_TAT);
    printf("Average Waiting Time = %f\n", average_WT);
}
