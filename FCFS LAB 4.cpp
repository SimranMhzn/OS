#include <stdio.h>

// Structure to represent a process
struct Process {
    int pid;      // Process ID
    int arrival;  // Arrival time
    int burst;    // Burst time
    int start;    // Start time
    int finish;   // Finish time
    int waiting;  // Waiting time
    int turnaround; // Turnaround time
};

void calculateTimes(struct Process processes[], int n) {
    int currentTime = 0;

    for (int i = 0; i < n; i++) {
        // Calculate start time
        if (currentTime < processes[i].arrival) {
            currentTime = processes[i].arrival;
        }
        processes[i].start = currentTime;

        // Calculate finish time
        processes[i].finish = processes[i].start + processes[i].burst;
        currentTime = processes[i].finish;

        // Calculate waiting and turnaround times
        processes[i].turnaround = processes[i].finish - processes[i].arrival;
        processes[i].waiting = processes[i].turnaround - processes[i].burst;
    }
}

void displayProcesses(struct Process processes[], int n) {
    printf("\nPID\tArrival\tBurst\tStart\tFinish\tWaiting\tTurnaround\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               processes[i].pid,
               processes[i].arrival,
               processes[i].burst,
               processes[i].start,
               processes[i].finish,
               processes[i].waiting,
               processes[i].turnaround);
    }
}

void sortProcessesByArrival(struct Process processes[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (processes[j].arrival > processes[j + 1].arrival) {
                struct Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }
}

int main() {
    int n;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];

    for (int i = 0; i < n; i++) {
        processes[i].pid = i + 1;
        printf("\nEnter arrival time for process %d: ", processes[i].pid);
        scanf("%d", &processes[i].arrival);
        printf("Enter burst time for process %d: ", processes[i].pid);
        scanf("%d", &processes[i].burst);
    }

    sortProcessesByArrival(processes, n);
    calculateTimes(processes, n);
    displayProcesses(processes, n);

    // Calculate and display average waiting and turnaround times
    float totalWaiting = 0, totalTurnaround = 0;
    for (int i = 0; i < n; i++) {
        totalWaiting += processes[i].waiting;
        totalTurnaround += processes[i].turnaround;
    }

    printf("\nAverage waiting time: %.2f\n", totalWaiting / n);
    printf("Average turnaround time: %.2f\n", totalTurnaround / n);

    return 0;
}

