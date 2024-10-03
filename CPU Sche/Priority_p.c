#include <stdio.h>
#include <stdbool.h>
#include <limits.h>  // for INT_MAX

void PrempPriority()
{
    printf("Enter the number of processes: ");
    int n;
    scanf("%d", &n);

    int pid[n];
    int at[n];
    int bt[n];
    int ct[n];
    int ta[n];
    int wt[n];
    int rt[n];  // Array to store response times
    int f[n];
    int k[n];
    int priority[n];
    int i, st = 0, tot = 0;

    for (i = 0; i < n; i++)
    {
        pid[i] = i + 1;
        printf("Enter arrival time for process %d: ", i + 1);
        scanf("%d", &at[i]);
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &bt[i]);
        k[i] = bt[i];  // Store original burst times
        f[i] = 0;      // Flag to check if the process is finished
        rt[i] = -1;    // Initialize response times to -1
        printf("Enter priority for process %d: ", i + 1);
        scanf("%d", &priority[i]);  // Store priority
    }

    while (true)
    {
        int min = INT_MAX, c = -1;  // Use INT_MAX for min and -1 for c (to indicate no process selected)
        if (tot == n)  // If all processes are finished, break the loop
            break;

        for (i = 0; i < n; i++)
        {
            if (at[i] <= st && f[i] == 0 && priority[i] < min)
            {
                min = priority[i];
                c = i;
            }
        }

        if (c == -1)
            st++;  // If no process is found, increment the system time
        else
        {
            if (rt[c] == -1)
                rt[c] = st - at[c];  // Set response time when the process starts execution for the first time
            bt[c]--;  // Decrement burst time of the selected process
            st++;  // Increment the system time
            if (bt[c] == 0)
            {
                ct[c] = st;  // Set completion time
                f[c] = 1;  // Mark the process as finished
                tot++;
            }
        }
    }

    for (i = 0; i < n; i++)
    {
        ta[i] = ct[i] - at[i];
        wt[i] = ta[i] - k[i];
    }

    printf("\nPid\tArrival\tBurst\tComplete\tTurn\tWaiting\tPriority\tResponse\n");
    for (i = 0; i < n; i++)
    {
        printf("%d\t%d\t%d\t%d\t\t%d\t%d\t%d\t\t%d\n", pid[i], at[i], k[i], ct[i], ta[i], wt[i], priority[i], rt[i]);
    }
}

int main()
{
    PrempPriority();
    return 0;
}
