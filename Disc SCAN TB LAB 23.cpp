#include <stdio.h>
#include <stdlib.h>

// Function to sort an array in ascending order
void sort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// SCAN Disk Scheduling Algorithm
void scanDiskScheduling(int requests[], int numRequests, int initialPosition, int diskSize, int direction) {
    int totalHeadMovement = 0;
    int currentPosition = initialPosition;

    // Sort the requests for easier processing
    sort(requests, numRequests);

    printf("Order of service:\n");

    // Depending on the direction, process requests
    if (direction == 1) { // Moving towards higher track numbers (upwards)
        // Process requests greater than or equal to the current position
        for (int i = 0; i < numRequests; i++) {
            if (requests[i] >= currentPosition) {
                printf("%d ", requests[i]);
                totalHeadMovement += abs(requests[i] - currentPosition);
                currentPosition = requests[i];
            }
        }

        // Move to the end of the disk if not already there
        if (currentPosition < diskSize - 1) {
            totalHeadMovement += abs((diskSize - 1) - currentPosition);
            currentPosition = diskSize - 1;
            printf("%d ", currentPosition); // End of disk
        }

        // Process requests less than the initial position (reverse direction)
        for (int i = numRequests - 1; i >= 0; i--) {
            if (requests[i] < initialPosition) {
                printf("%d ", requests[i]);
                totalHeadMovement += abs(requests[i] - currentPosition);
                currentPosition = requests[i];
            }
        }
    } else { // Moving towards lower track numbers (downwards)
        // Process requests less than or equal to the current position
        for (int i = numRequests - 1; i >= 0; i--) {
            if (requests[i] <= currentPosition) {
                printf("%d ", requests[i]);
                totalHeadMovement += abs(requests[i] - currentPosition);
                currentPosition = requests[i];
            }
        }

        // Move to the start of the disk if not already there
        if (currentPosition > 0) {
            totalHeadMovement += abs(currentPosition - 0);
            currentPosition = 0;
            printf("%d ", currentPosition); // Start of disk
        }

        // Process requests greater than the initial position (reverse direction)
        for (int i = 0; i < numRequests; i++) {
            if (requests[i] > initialPosition) {
                printf("%d ", requests[i]);
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

    // Input the initial direction of movement (1 for up, 0 for down)
    printf("Enter the initial direction (1 for up, 0 for down): ");
    scanf("%d", &direction);

    // Implementing the SCAN disk scheduling algorithm
    scanDiskScheduling(requests, numRequests, initialPosition, diskSize, direction);

    return 0;
}

