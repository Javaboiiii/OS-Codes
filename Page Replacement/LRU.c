#include <stdio.h>

void lruPageReplacement(int pages[], int n, int capacity)
{
    int frame[capacity];
    int pageFaults = 0;
    int pageHits = 0;
    int recentCount = 0;
    int recent[capacity];

    for (int i = 0; i < capacity; i++)
    {
        frame[i] = -1;
        recent[i] = 0;
    }

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
                recent[j] = recentCount++;
                pageHits++;
                break;
            }
        }

        if (!pageFound)
        {
            // Page is not present, find the least recently used page in the frame
            int lruIndex = 0;
            for (int j = 1; j < capacity; j++)
            {
                if (recent[j] < recent[lruIndex])
                {
                    lruIndex = j;
                }
            }

            // Replace the least recently used page with the new page
            frame[lruIndex] = page;
            recent[lruIndex] = recentCount++;
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

    lruPageReplacement(pages, n, capacity);

    return 0;
}
