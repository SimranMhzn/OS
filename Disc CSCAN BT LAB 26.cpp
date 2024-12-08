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

// C-SCAN Disk Scheduling Algorithm (Bottom-to-Top Approach)
void cscanDiskSchedulingBottomToTop(int requests[], int numRequests, int initialPosition, int diskSize) {
    int totalHeadMovement = 0;
    int currentPosition = initialPosition;

    // Sort the requests in ascending order
    sort(requests, numRequests);

    printf("Order of service:\n");

    // Step 1: Process requests less than or equal to the current position (moving downward)
    for (int i = numRequests - 1; i >= 0; i--) {
        if (requests[i] <= currentPosition) {
            printf("%d ", requests[i]);
            totalHeadMovement += abs(currentPosition - requests[i]);
            currentPosition = requests[i];
        }
    }

    // Step 2: Move to the lowest track (if not already there)
    if (currentPosition > 0) {
        totalHeadMovement += currentPosition; // Add movement to track 0
        currentPosition = 0;
        printf("%d ", currentPosition); // Lowest track
    }

    // Step 3: Wrap around to the highest track
    totalHeadMovement += (diskSize - 1); // Movement from 0 to the highest track
    currentPosition = diskSize - 1;
    printf("%d ", currentPosition); // Highest track

    // Step 4: Process remaining requests in descending order greater than the initial position
    for (int i = numRequests - 1; i >= 0; i--) {
        if (requests[i] > initialPosition) {
            printf("%d ", requests[i]);
            totalHeadMovement += abs(currentPosition - requests[i]);
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
    cscanDiskSchedulingBottomToTop(requests, numRequests, initialPosition, diskSize);

    return 0;
}

