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

// LOOK Disk Scheduling Algorithm (Top-to-Bottom Approach)
void lookDiskSchedulingTopToBottom(int requests[], int numRequests, int initialPosition, int diskSize) {
    int totalHeadMovement = 0;
    int currentPosition = initialPosition;

    // Sort the requests in ascending order
    sort(requests, numRequests);

    // Find the index where the current position fits in the sorted array
    int i = 0;
    while (i < numRequests && requests[i] < currentPosition) {
        i++;
    }

    printf("Order of service:\n");

    // Step 1: Process requests greater than or equal to the current position (moving upward)
    for (int j = i; j < numRequests; j++) {
        printf("%d ", requests[j]);
        totalHeadMovement += abs(currentPosition - requests[j]);
        currentPosition = requests[j];
    }

    // Step 2: Process requests less than the initial position (moving downward)
    for (int j = i - 1; j >= 0; j--) {
        printf("%d ", requests[j]);
        totalHeadMovement += abs(currentPosition - requests[j]);
        currentPosition = requests[j];
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

    // Input the disk size (number of tracks)
    printf("Enter the disk size (number of tracks): ");
    scanf("%d", &diskSize);

    // Implementing the LOOK disk scheduling algorithm
    lookDiskSchedulingTopToBottom(requests, numRequests, initialPosition, diskSize);

    return 0;
}

