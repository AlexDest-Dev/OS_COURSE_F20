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
    int const_burst_time;
    bool used;
};

int compare_processes(struct process A, struct process B) {
    if (A.arrival_time > B.arrival_time) {
        return 1;
    }
    else if (A.arrival_time < B.arrival_time) {
        return -1;
    }
    else return 0;
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
    int quantum_time;
    printf("Enter quantum time for Robin Round algorithm:\n");
    scanf("%d", &quantum_time);
    int processes_number;
    printf("Enter number of processes:\n");
    scanf("%d", &processes_number);
    struct process* processes = malloc(processes_number * sizeof(struct process));
    printf("Enter Arrival Time and Burst Time for each process:\n");
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
        processes[i].completion_time = 0;
        processes[i].turnaround_time = 0;
        processes[i].waiting_time = 0;
        processes[i].const_burst_time = processes[i].burst_time;
    }
    AT_sort_processes(processes, processes_number);
    int current_time = 0;
    struct process temp_process1 = processes[0];
    while (true) {
        bool all_processes_used = true;
        bool changes_on_current_time = false;
        for (int j = 0; j < processes_number; j++) {
            struct process* temp_process = &processes[j];
            if (!processes[j].used && processes[j].arrival_time <= current_time) {
                if (processes[j].burst_time - quantum_time <= 0) {
                    processes[j].used = true;
                    processes[j].completion_time = current_time + processes[j].burst_time;
                }
                else {
                    processes[j].completion_time = current_time + quantum_time;
                }
                processes[j].turnaround_time = processes[j].completion_time - processes[j].arrival_time;
                processes[j].waiting_time = processes[j].turnaround_time - processes[j].const_burst_time;
                processes[j].burst_time -= quantum_time;
                current_time = processes[j].completion_time;
                changes_on_current_time = true;
            }
        }
        if (!changes_on_current_time) {
            current_time++;
            continue;
        }
        for (int i = 0; i < processes_number; i++) {
            if (!processes[i].used) {
                all_processes_used = false;
                break;
            }
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
               processes[i].const_burst_time, processes[i].completion_time, processes[i].turnaround_time, processes[i].waiting_time);
    }
    printf("Average Turnaround Time = %f\n", average_TAT);
    printf("Average Waiting Time = %f\n", average_WT);
}
