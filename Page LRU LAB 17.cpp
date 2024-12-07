#include <stdio.h>

#define MAX_FRAMES 10  // Define the maximum number of frames for simplicity

void lruPageReplacement(int pages[], int numPages, int numFrames) {
    int frames[MAX_FRAMES];
    int pageFaults = 0;
    int recent[MAX_FRAMES];
    
    // Initialize frames to -1 (empty)
    for (int i = 0; i < numFrames; i++) {
        frames[i] = -1;
        recent[i] = -1;
    }

    for (int i = 0; i < numPages; i++) {
        int page = pages[i];
        int found = 0;

        // Check if the page is already in one of the frames (a hit)
        for (int j = 0; j < numFrames; j++) {
            if (frames[j] == page) {
                found = 1;
                recent[j] = i;  // Update the most recent usage
                break;
            }
        }

        // If the page is not found in the frames, it's a page fault
        if (!found) {
            int lruIndex = 0;

            // Find the least recently used page
            for (int j = 1; j < numFrames; j++) {
                if (recent[j] < recent[lruIndex]) {
                    lruIndex = j;
                }
            }

            // Replace the LRU page with the new page
            frames[lruIndex] = page;
            recent[lruIndex] = i;  // Update the most recent usage
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

    // Implementing the LRU page replacement algorithm
    lruPageReplacement(pages, numPages, numFrames);

    return 0;
}

