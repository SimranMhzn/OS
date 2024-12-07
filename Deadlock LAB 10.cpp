#include <stdio.h>
#include <stdbool.h>

#define MAX_PROCESSES 10
#define MAX_RESOURCES 10

void deadlockDetection(int processes[], int available[], int max[][MAX_RESOURCES], int allocation[][MAX_RESOURCES], int need[][MAX_RESOURCES], int n, int m) {
    bool finish[MAX_PROCESSES] = {false};
    int work[MAX_RESOURCES];

    for (int i = 0; i < m; i++) {
        work[i] = available[i];
    }

    printf("\nSafe Sequence (if exists): \n");
    int safeSequence[MAX_PROCESSES], index = 0;

    for (int count = 0; count < n; count++) {
        bool found = false;
        for (int i = 0; i < n; i++) {
            if (!finish[i]) {
                bool canProceed = true;
                for (int j = 0; j < m; j++) {
                    if (need[i][j] > work[j]) {
                        canProceed = false;
                        break;
                    }
                }

                if (canProceed) {
                    for (int j = 0; j < m; j++) {
                        work[j] += allocation[i][j];
                    }
                    safeSequence[index++] = processes[i];
                    finish[i] = true;
                    found = true;
                }
            }
        }

        if (!found) {
            printf("Deadlock detected.\n");
            return;
        }
    }

    printf("System is in a safe state. Safe sequence is: \n");
    for (int i = 0; i < n; i++) {
        printf("P%d ", safeSequence[i]);
    }
    printf("\n");
}

int main() {
    int n, m;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    printf("Enter the number of resources: ");
    scanf("%d", &m);

    int processes[MAX_PROCESSES];
    for (int i = 0; i < n; i++) {
        processes[i] = i;
    }

    int available[MAX_RESOURCES];
    printf("\nEnter the available resources: \n");
    for (int i = 0; i < m; i++) {
        scanf("%d", &available[i]);
    }

    int max[MAX_PROCESSES][MAX_RESOURCES];
    printf("\nEnter the maximum resource matrix: \n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &max[i][j]);
        }
    }

    int allocation[MAX_PROCESSES][MAX_RESOURCES];
    printf("\nEnter the allocation matrix: \n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &allocation[i][j]);
        }
    }

    int need[MAX_PROCESSES][MAX_RESOURCES];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }

    deadlockDetection(processes, available, max, allocation, need, n, m);

    return 0;
}

