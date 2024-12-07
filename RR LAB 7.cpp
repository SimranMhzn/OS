#include <stdio.h>
#include <stdbool.h>

// Structure to represent a process
struct Process {
    int pid;      // Process ID
    int arrival;  // Arrival time
    int burst;    // Burst time
    int remaining; // Remaining time
    int start;    // Start time
    int finish;   // Finish time
    int waiting;  // Waiting time
    int turnaround; // Turnaround time
    bool started; // Flag to indicate if the process has started
};

void calculateTimes(struct Process processes[], int n, int quantum) {
    int currentTime = 0;
    int completedProcesses = 0;

    for (int i = 0; i < n; i++) {
        processes[i].remaining = processes[i].burst;
        processes[i].started = false;
    }

    while (completedProcesses < n) {
        bool allIdle = true;

        for (int i = 0; i < n; i++) {
            if (processes[i].arrival <= currentTime && processes[i].remaining > 0) {
                allIdle = false;

                // If process starts for the first time
                if (!processes[i].started) {
                    processes[i].start = currentTime;
                    processes[i].started = true;
                }

                // Execute process for a time quantum or until completion
                int execTime = (processes[i].remaining > quantum) ? quantum : processes[i].remaining;
                processes[i].remaining -= execTime;
                currentTime += execTime;

                // If the process is completed
                if (processes[i].remaining == 0) {
                    processes[i].finish = currentTime;
                    processes[i].turnaround = processes[i].finish - processes[i].arrival;
                    processes[i].waiting = processes[i].turnaround - processes[i].burst;
                    completedProcesses++;
                }
            }
        }

        // If no process was executed, advance time
        if (allIdle) {
            currentTime++;
        }
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

int main() {
    int n, quantum;

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

    printf("\nEnter time quantum: ");
    scanf("%d", &quantum);

    calculateTimes(processes, n, quantum);
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

