#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

// Structure to represent a process
struct Process {
    int pid;      // Process ID
    int arrival;  // Arrival time
    int burst;    // Burst time
    int priority; // Priority (lower number = higher priority)
    int start;    // Start time
    int finish;   // Finish time
    int waiting;  // Waiting time
    int turnaround; // Turnaround time
    bool completed; // Completion flag
};

void calculateTimes(struct Process processes[], int n) {
    int currentTime = 0;
    int completedProcesses = 0;

    for (int i = 0; i < n; i++) {
        processes[i].completed = false;
    }

    while (completedProcesses < n) {
        int highestPriority = INT_MAX;
        int chosenProcess = -1;

        // Find the process with the highest priority
        for (int i = 0; i < n; i++) {
            if (!processes[i].completed && processes[i].arrival <= currentTime && processes[i].priority < highestPriority) {
                highestPriority = processes[i].priority;
                chosenProcess = i;
            }
        }

        if (chosenProcess == -1) {
            currentTime++;
            continue;
        }

        // Process execution
        processes[chosenProcess].start = currentTime;
        currentTime += processes[chosenProcess].burst;
        processes[chosenProcess].finish = currentTime;
        processes[chosenProcess].turnaround = processes[chosenProcess].finish - processes[chosenProcess].arrival;
        processes[chosenProcess].waiting = processes[chosenProcess].turnaround - processes[chosenProcess].burst;
        processes[chosenProcess].completed = true;

        completedProcesses++;
    }
}

void displayProcesses(struct Process processes[], int n) {
    printf("\nPID\tArrival\tBurst\tPriority\tStart\tFinish\tWaiting\tTurnaround\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               processes[i].pid,
               processes[i].arrival,
               processes[i].burst,
               processes[i].priority,
               processes[i].start,
               processes[i].finish,
               processes[i].waiting,
               processes[i].turnaround);
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
        printf("Enter priority for process %d (lower number = higher priority): ", processes[i].pid);
        scanf("%d", &processes[i].priority);
    }

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

