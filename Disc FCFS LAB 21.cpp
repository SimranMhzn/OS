#include <stdio.h>
#include <stdlib.h>

// Function to calculate the total head movement using FCFS
void fcfsDiskScheduling(int requests[], int numRequests, int initialPosition) {
    int totalHeadMovement = 0;
    int currentPosition = initialPosition;

    printf("Order of service:\n");

    // Print the initial position of the head
    printf("%d -> ", currentPosition);

    // Process each request in the order they arrive
    for (int i = 0; i < numRequests; i++) {
        int nextRequest = requests[i];
        totalHeadMovement += abs(nextRequest - currentPosition);
        currentPosition = nextRequest;
        printf("%d ", nextRequest);
        if (i < numRequests - 1) {
            printf("-> ");
        }
    }

    printf("\nTotal head movement: %d\n", totalHeadMovement);
}

int main() {
    int numRequests, initialPosition;

    // Input the number of disk I/O requests
    printf("Enter the number of disk I/O requests: ");
    scanf("%d", &numRequests);
    int requests[numRequests];

    // Input the requests
    printf("Enter the disk I/O requests:\n");
    for (int i = 0; i < numRequests; i++) {
        scanf("%d", &requests[i]);
    }

    // Input the initial position of the disk head
    printf("Enter the initial position of the disk head: ");
    scanf("%d", &initialPosition);

    // Implementing the FCFS disk scheduling algorithm
    fcfsDiskScheduling(requests, numRequests, initialPosition);

    return 0;
}

