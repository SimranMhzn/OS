#include <stdio.h>

#define MAX_FRAMES 10  // Define the maximum number of frames for simplicity

// Function to find the index of the page that will not be used for the longest time in the future
int findOptimalPage(int frames[], int numFrames, int pages[], int numPages, int currentIndex) {
    int maxDistance = -1;
    int indexToReplace = -1;

    for (int i = 0; i < numFrames; i++) {
        int found = 0;
        for (int j = currentIndex; j < numPages; j++) {
            if (frames[i] == pages[j]) {
                found = 1;
                if (j > maxDistance) {
                    maxDistance = j;
                    indexToReplace = i;
                }
                break;
            }
        }
        if (!found) {
            return i; // If the page is not found in the future, replace it immediately
        }
    }
    return indexToReplace;
}

void optimalPageReplacement(int pages[], int numPages, int numFrames) {
    int frames[MAX_FRAMES];
    int pageFaults = 0;

    // Initialize frames to -1 (empty)
    for (int i = 0; i < numFrames; i++) {
        frames[i] = -1;
    }

    for (int i = 0; i < numPages; i++) {
        int page = pages[i];
        int found = 0;

        // Check if the page is already in one of the frames (a hit)
        for (int j = 0; j < numFrames; j++) {
            if (frames[j] == page) {
                found = 1;
                break;
            }
        }

        // If the page is not found in the frames, it's a page fault
        if (!found) {
            int indexToReplace = findOptimalPage(frames, numFrames, pages, numPages, i + 1);
            frames[indexToReplace] = page;
            pageFaults++;
        }

        // Print the current status of the frames and whether it was a hit or a fault
        printf("Page %d: [", page);
        for (int j = 0; j < numFrames; j++) {
            if (frames[j] != -1) {
                printf("%d ", frames[j]);
            } else {
                printf("- ");
            }
        }
        if (found) {
            printf("] (Hit)\n");
        } else {
            printf("] (Fault)\n");
        }
    }

    // Print the total number of page faults
    printf("Total page faults: %d\n", pageFaults);
}

int main() {
    int numPages, numFrames;

    // Input the number of pages and frames
    printf("Enter the number of pages: ");
    scanf("%d", &numPages);
    int pages[numPages];

    printf("Enter the number of frames: ");
    scanf("%d", &numFrames);

    printf("Enter the page reference string:\n");
    for (int i = 0; i < numPages; i++) {
        scanf("%d", &pages[i]);
    }

    // Implementing the Optimal Page Replacement algorithm
    optimalPageReplacement(pages, numPages, numFrames);

    return 0;
}

