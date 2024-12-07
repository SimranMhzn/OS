#include <stdio.h>
#include <stdlib.h>

// Function to find the SCAN disk scheduling order
void scanDiskScheduling(int requests[], int numRequests, int initialPosition, int diskSize, int direction) {
    int totalHeadMovement = 0;
    int currentPosition = initialPosition;
    int i, j;

    // Sort the requests array for easier processing
    for (i = 0; i < numRequests - 1; i++) {
        for (j = 0; j < numRequests - i - 1; j++) {
            if (requests[j] > requests[j + 1]) {
                int temp = requests[j];
                requests[j] = requests[j + 1];
                requests[j + 1] = temp;
            }
        }
    }

    printf("Order of service:\n");

    if (direction == 0) {  // Moving towards the lower end (left)
        for (i = numRequests - 1; i >= 0; i--) {
            if (requests[i] <= currentPosition) {
                printf("%d ", requests[i]);
                totalHeadMovement += abs(requests[i] - currentPosition);
                currentPosition = requests[i];
            }
        }
        // Move to the beginning (track 0)
        totalHeadMovement += currentPosition;
        currentPosition = 0;

        // Move towards the higher end (right)
        for (i = 0; i < numRequests; i++) {
            if (requests[i] >= currentPosition) {
                printf("-> %d", requests[i]);
                totalHeadMovement += abs(requests[i] - currentPosition);
                currentPosition = requests[i];
            }
        }
    } else {  // Moving towards the higher end (right)
        for (i = 0; i < numRequests; i++) {
            if (requests[i] >= currentPosition) {
                printf("%d ", requests[i]);
                totalHeadMovement += abs(requests[i] - currentPosition);
                currentPosition = requests[i];
            }
        }
        // Move to the end (disk size - 1)
        totalHeadMovement += (diskSize - 1 - currentPosition);
        currentPosition = diskSize - 1;

        // Move towards the lower end (left)
        for (i = numRequests - 1; i >= 0; i--) {
            if (requests[i] <= currentPosition) {
                printf("-> %d", requests[i]);
                totalHeadMovement += abs(requests[i] - currentPosition);
                currentPosition = requests[i];
            }
        }
    }

    printf("\nTotal head movement: %d\n", totalHeadMovement);
}

int main() {
    int numRequests, initialPosition, diskSize, direction;

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

    // Input the disk size (total number of tracks)
    printf("Enter the disk size (number of tracks): ");
    scanf("%d", &diskSize);

    // Input the direction of the initial movement (0 for left, 1 for right)
    printf("Enter the initial direction (0 for left, 1 for right): ");
    scanf("%d", &direction);

    // Implementing the SCAN disk scheduling algorithm
    scanDiskScheduling(requests, numRequests, initialPosition, diskSize, direction);

    return 0;
}

