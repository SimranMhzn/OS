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

// C-SCAN Disk Scheduling Algorithm (Top-to-Bottom Approach)
void cscanDiskScheduling(int requests[], int numRequests, int initialPosition, int diskSize) {
    int totalHeadMovement = 0;
    int currentPosition = initialPosition;

    // Sort the requests for easier processing
    sort(requests, numRequests);

    printf("Order of service:\n");

    // Process requests greater than or equal to the current position (moving upwards)
    for (int i = 0; i < numRequests; i++) {
        if (requests[i] >= currentPosition) {
            printf("%d ", requests[i]);
            totalHeadMovement += abs(requests[i] - currentPosition);
            currentPosition = requests[i];
        }
    }

    // Move to the highest track (if not already there)
    if (currentPosition < diskSize - 1) {
        totalHeadMovement += abs((diskSize - 1) - currentPosition);
        currentPosition = diskSize - 1;
        printf("%d ", currentPosition); // Highest track
    }

    // Wrap around to the lowest track
    totalHeadMovement += currentPosition; // Add movement from highest to 0
    currentPosition = 0;
    printf("%d ", currentPosition); // Lowest track

    // Process requests less than the initial position (from the bottom)
    for (int i = 0; i < numRequests; i++) {
        if (requests[i] < initialPosition) {
            printf("%d ", requests[i]);
            totalHeadMovement += abs(requests[i] - currentPosition);
            currentPosition = requests[i];
        }
    }

    printf("\nTotal head movement: %d\n", totalHeadMovement);
}

int main() {
    int numRequests, initialPosition, diskSize;

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

    // Implementing the C-SCAN disk scheduling algorithm
    cscanDiskScheduling(requests, numRequests, initialPosition, diskSize);

    return 0;
}

