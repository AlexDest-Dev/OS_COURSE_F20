#include <stdio.h>

int processes_number;
void sort_data(int processes_data[processes_number][6], int prop) {
    for (int i = 0; i < processes_number; i++) {
        for (int j = i + 1; j < processes_number; j++) {
            if (processes_data[i][prop] > processes_data[j][prop]) {
                int t0, t1, t5;
                t0 = processes_data[i][0];
                t1 = processes_data[i][1];
                t5 = processes_data[i][5];
                processes_data[i][0] = processes_data[j][0];
                processes_data[i][1] = processes_data[j][1];
                processes_data[i][5] = processes_data[j][5];
                processes_data[j][0] = t0;
                processes_data[j][1] = t1;
                processes_data[j][5] = t5;
            }
        }
    }
}
int main() {
    printf("Enter number of processes:\n");
    scanf("%d", &processes_number);
    int processes_data[processes_number][6];
    printf("Enter Arrival Time and Burst Time for each process:\n");
    for (int i = 0; i < processes_number; i++) {
        printf("Arrival Time of Process [%d]:\n", i+1);
        scanf("%d", &processes_data[i][0]);
        printf("Burst Time of Process [%d]:\n", i+1);
        scanf("%d", &processes_data[i][1]);
        processes_data[i][5] = i + 1;
    }
    sort_data(&processes_data, 0);
    // 0 - AT
    // 1 - BT
    // 2 - CT
    // 3 - TAT
    // 4 - WT
    for (int i = 0; i < processes_number; i++) {
        if (i == 0) {
            processes_data[i][2] = processes_data[i][0] + processes_data[i][1];
            processes_data[i][3] = processes_data[i][2] - processes_data[i][0];
            processes_data[i][4] = processes_data[i][3] - processes_data[i][1];
        }
        else {
            if (processes_data[i][0] <= processes_data[i-1][2]) {
                processes_data[i][2] = processes_data[i-1][2] + processes_data[i][1];
            }
            else {
                processes_data[i][2] = processes_data[i][0] + processes_data[i][1];
            }
            processes_data[i][3] = processes_data[i][2] - processes_data[i][0];
            processes_data[i][4] = processes_data[i][3] - processes_data[i][1];
        }
    }

    float average_TAT = 0;
    float average_WT = 0;
    for (int i = 0; i < processes_number; i++) {
        average_TAT += (float)processes_data[i][3];
        average_WT+= (float)processes_data[i][4];
    }
    average_TAT /= (float)processes_number;
    average_WT /= (float)processes_number;
    printf("P#\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < processes_number; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", processes_data[i][5], processes_data[i][0],
                processes_data[i][1], processes_data[i][2], processes_data[i][3], processes_data[i][4]);
    }
    printf("Average Turnaround Time = %f\n", average_TAT);
    printf("Average Waiting Time = %f\n", average_WT);
}
