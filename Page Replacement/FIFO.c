#include <stdio.h>
void fifoPageReplacement(int pages[], int n, int capacity)
{
    int frame[capacity];
    int pageFaults = 0;
    int pageHits = 0;
    int front = 0; // Pointer to the first page in the frame

    for (int i = 0; i < capacity; i++)
        frame[i] = -1; // Initialize frame with -1 indicating an empty slot

    printf("Incoming\tFrame\n");

    for (int i = 0; i < n; i++)
    {
        int page = pages[i];
        int pageFound = 0;

        // Check if the page is already present in the frame
        for (int j = 0; j < capacity; j++)
        {
            if (frame[j] == page)
            {
                pageFound = 1;
                pageHits++;
                break;
            }
        }

        if (!pageFound)
        {
            // Page is not present, replace the oldest page in the frame
            frame[front] = page;
            front = (front + 1) % capacity;
            pageFaults++;
        }

        // Print the current page and frame status
        printf("%d\t\t", page);
        for (int j = 0; j < capacity; j++)
        {
            if (frame[j] != -1)
                printf("%d\t\t", frame[j]);
            else
                printf("-\t\t");
        }
        printf("\n");
    }

    printf("\nTotal Page Faults: %d\n", pageFaults);
    printf("Total Page Hits: %d\n", pageHits);
}

int main()
{
    int n;

    // Input the number of pages
    printf("Enter the number of pages: ");
    scanf("%d", &n);

    int pages[n];

    // Input the sequence of page requests
    printf("Enter the sequence of page requests:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &pages[i]);

    int capacity;

    // Input the number of frames
    printf("Enter the number of frames: ");
    scanf("%d", &capacity);

    fifoPageReplacement(pages, n, capacity);

    return 0;
}
