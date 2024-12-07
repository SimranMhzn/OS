#include <stdio.h>
#include <stdbool.h>

typedef struct {
    int size;
    bool isAllocated;
} Partition;

void allocateMemory(Partition partitions[], int numPartitions, int processSizes[], int numProcesses) {
    int lastAllocatedIndex = 0; // Start allocation from the first partition
    
    for (int i = 0; i < numProcesses; i++) {
        bool allocated = false;
        
        // Start searching from the last allocated index
        for (int j = lastAllocatedIndex; j < numPartitions; j++) {
            if (!partitions[j].isAllocated && partitions[j].size >= processSizes[i]) {
                partitions[j].isAllocated = true; // Allocate the partition
                printf("Process %d of size %d allocated to partition %d\n", i + 1, processSizes[i], j + 1);
                lastAllocatedIndex = j; // Update the last allocated index
                allocated = true;
                break; // Move to the next process
            }
        }
        
        // If allocation didn't happen in the first pass, continue from the beginning
        if (!allocated) {
            for (int j = 0; j < lastAllocatedIndex; j++) {
                if (!partitions[j].isAllocated && partitions[j].size >= processSizes[i]) {
                    partitions[j].isAllocated = true; // Allocate the partition
                    printf("Process %d of size %d allocated to partition %d\n", i + 1, processSizes[i], j + 1);
                    lastAllocatedIndex = j; // Update the last allocated index
                    allocated = true;
                    break; // Move to the next process
                }
            }
        }
        
        if (!allocated) {
            printf("Process %d of size %d could not be allocated\n", i + 1, processSizes[i]);
        }
    }
}

int main() {
    int numPartitions, numProcesses;

    // Input the number of partitions and their sizes
    printf("Enter the number of partitions: ");
    scanf("%d", &numPartitions);
    Partition partitions[numPartitions];

    printf("Enter the sizes of the partitions:\n");
    for (int i = 0; i < numPartitions; i++) {
        scanf("%d", &partitions[i].size);
        partitions[i].isAllocated = false; // Initialize as not allocated
    }

    // Input the number of processes and their sizes
    printf("Enter the number of processes: ");
    scanf("%d", &numProcesses);
    int processSizes[numProcesses];

    printf("Enter the sizes of the processes:\n");
    for (int i = 0; i < numProcesses; i++) {
        scanf("%d", &processSizes[i]);
    }

    // Implementing the Next Fit strategy
    allocateMemory(partitions, numPartitions, processSizes, numProcesses);

    return 0;
}

