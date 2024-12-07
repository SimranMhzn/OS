#include <stdio.h>

#define MAX_FRAMES 10  // Define the maximum number of frames for simplicity

typedef struct {
    int page;
    int referenced;  // 1 if the page has been referenced, 0 otherwise
    int modified;    // 1 if the page has been modified, 0 otherwise
} Page;

void nruPageReplacement(int pages[], int numPages, int numFrames) {
    Page frames[MAX_FRAMES];
    int pageFaults = 0;

    // Initialize frames and their properties
    for (int i = 0; i < numFrames; i++) {
        frames[i].page = -1;        // -1 indicates an empty frame
        frames[i].referenced = 0;   // Not referenced initially
        frames[i].modified = 0;     // Not modified initially
    }

    for (int i = 0; i < numPages; i++) {
        int page = pages[i];
        int found = 0;
        int minClass = 4;  // Class 0 is the lowest (best candidate for replacement)
        int replaceIndex = -1;

        // Check if the page is already in one of the frames (a hit)
        for (int j = 0; j < numFrames; j++) {
            if (frames[j].page == page) {
                found = 1;
                frames[j].referenced = 1;  // Mark as referenced
                break;
            }
        }

        // If the page is not found in the frames, it's a page fault
        if (!found) {
            // Find the page to replace based on the NRU classification
            for (int j = 0; j < numFrames; j++) {
                if (frames[j].page == -1) {
                    // If there is an empty frame, use it immediately
                    replaceIndex = j;
                    break;
                }

                int currentClass = (frames[j].referenced << 1) | frames[j].modified;
                if (currentClass < minClass) {
                    minClass = currentClass;
                    replaceIndex = j;
                }
            }

            // Replace the page and mark as referenced and unmodified
            frames[replaceIndex].page = page;
            frames[replaceIndex].referenced = 1;
            frames[replaceIndex].modified = 0;
            pageFaults++;
        }

        // Print the current status of the frames and whether it was a hit or a fault
        printf("Page %d: [", page);
        for (int j = 0; j < numFrames; j++) {
            if (frames[j].page != -1) {
                printf("%d ", frames[j].page);
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

    // Implementing the NRU page replacement algorithm
    nruPageReplacement(pages, numPages, numFrames);

    return 0;
}

