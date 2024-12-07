#include <stdio.h>
#include <limits.h>

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
    int completed; // Completion flag
};

void calculateTimes(struct Process processes[], int n) {
    int currentTime = 0, completedProcesses = 0;

    for (int i = 0; i < n; i++) {
        processes[i].remaining = processes[i].burst; // Initialize remaining time
        processes[i].completed = 0;
    }

    while (completedProcesses < n) {
        int shortestJob = -1;
        int minRemaining = INT_MAX;

        // Find the process with the shortest remaining time
        for (int i = 0; i < n; i++) {
            if (processes[i].arrival <= currentTime && !processes[i].completed && processes[i].remaining < minRemaining) {
                minRemaining = processes[i].remaining;
                shortestJob = i;
            }
        }

        if (shortestJob == -1) {
            currentTime++;
            continue;
        }

        // If the process starts for the first time
        if (processes[shortestJob].remaining == processes[shortestJob].burst) {
            processes[shortestJob].start = currentTime;
        }

        // Execute the process for one unit of time
        processes[shortestJob].remaining--;
        currentTime++;

        // If the process is completed
        if (processes[shortestJob].remaining == 0) {
            processes[shortestJob].completed = 1;
            processes[shortestJob].finish = currentTime;
            processes[shortestJob].turnaround = processes[shortestJob].finish - processes[shortestJob].arrival;
            processes[shortestJob].waiting = processes[shortestJob].turnaround - processes[shortestJob].burst;
            completedProcesses++;
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

