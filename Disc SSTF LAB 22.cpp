#include <stdio.h>
#include <stdlib.h>

// Function to find the SSTF disk scheduling order
void sstfDiskScheduling(int requests[], int numRequests, int initialPosition) {
    int totalHeadMovement = 0;
    int currentPosition = initialPosition;
    int served[numRequests];
    int servedCount = 0;

    // Mark all requests as not yet served
    for (int i = 0; i < numRequests; i++) {
        served[i] = 0;
    }

    printf("Order of service:\n");

    // Process each request until all are served
    while (servedCount < numRequests) {
        int minSeekTime = 1000000;  // Large initial value
        int closestRequestIndex = -1;

        // Find the request with the shortest seek time
        for (int i = 0; i < numRequests; i++) {
            if (!served[i]) {
                int seekTime = abs(requests[i] - currentPosition);
                if (seekTime < minSeekTime) {
                    minSeekTime = seekTime;
                    closestRequestIndex = i;
                }
            }
        }

        // Serve the closest request
        served[closestRequestIndex] = 1;
        totalHeadMovement += minSeekTime;
        currentPosition = requests[closestRequestIndex];
        servedCount++;

        // Print the current request being serviced
        printf("%d ", currentPosition);
        if (servedCount < numRequests) {
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

    // Implementing the SSTF disk scheduling algorithm
    sstfDiskScheduling(requests, numRequests, initialPosition);

    return 0;
}

