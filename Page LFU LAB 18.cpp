#include <stdio.h>

#define MAX_FRAMES 10  // Define the maximum number of frames for simplicity

// Function to find the index of the page with the least frequency
int findLFUPage(int frames[], int frequency[], int numFrames) {
    int minFrequency = frequency[0];
    int indexToReplace = 0;

    // Find the page with the minimum frequency of access
    for (int i = 1; i < numFrames; i++) {
        if (frequency[i] < minFrequency) {
            minFrequency = frequency[i];
            indexToReplace = i;
        }
    }
    return indexToReplace;
}

void lfuPageReplacement(int pages[], int numPages, int numFrames) {
    int frames[MAX_FRAMES];
    int frequency[MAX_FRAMES];
    int pageFaults = 0;

    // Initialize frames and frequency arrays
    for (int i = 0; i < numFrames; i++) {
        frames[i] = -1;  // -1 indicates an empty frame
        frequency[i] = 0; // Initial frequency is 0
    }

    for (int i = 0; i < numPages; i++) {
        int page = pages[i];
        int found = 0;

        // Check if the page is already in one of the frames (a hit)
        for (int j = 0; j < numFrames; j++) {
            if (frames[j] == page) {
                found = 1;
                frequency[j]++; // Increment the frequency of the page
                break;
            }
        }

        // If the page is not found in the frames, it's a page fault
        if (!found) {
            int indexToReplace = findLFUPage(frames, frequency, numFrames);
            frames[indexToReplace] = page; // Replace the LFU page
            frequency[indexToReplace] = 1;  // Reset frequency of the new page
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

    // Implementing the LFU page replacement algorithm
    lfuPageReplacement(pages, numPages, numFrames);

    return 0;
}

