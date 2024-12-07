#include <stdio.h>

#define MAX_FRAMES 10  // Define the maximum number of frames for simplicity

void secondChancePageReplacement(int pages[], int numPages, int numFrames) {
    int frames[MAX_FRAMES];
    int referenced[MAX_FRAMES];
    int pageFaults = 0;
    int clockHand = 0;  // Index for the clock (circular queue)

    // Initialize frames and referenced bits
    for (int i = 0; i < numFrames; i++) {
        frames[i] = -1;        // -1 indicates an empty frame
        referenced[i] = 0;     // Referenced bit is 0 initially
    }

    for (int i = 0; i < numPages; i++) {
        int page = pages[i];
        int found = 0;

        // Check if the page is already in one of the frames (a hit)
        for (int j = 0; j < numFrames; j++) {
            if (frames[j] == page) {
                found = 1;
                referenced[j] = 1;  // Set the referenced bit
                break;
            }
        }

        // If the page is not found in the frames, it's a page fault
        if (!found) {
            // Search for a page with a referenced bit of 0 (second chance)
            while (referenced[clockHand] == 1) {
                // Clear the referenced bit and move the clock hand
                referenced[clockHand] = 0;
                clockHand = (clockHand + 1) % numFrames;
            }

            // Replace the page at the current clock hand position
            frames[clockHand] = page;
            referenced[clockHand] = 1;  // Set the referenced bit for the new page
            clockHand = (clockHand + 1) % numFrames;  // Move the clock hand
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

    // Implementing the Second Chance page replacement algorithm
    secondChancePageReplacement(pages, numPages, numFrames);

    return 0;
}

