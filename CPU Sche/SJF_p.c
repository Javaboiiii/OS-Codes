#include <stdio.h>
#include <stdbool.h>
#include <limits.h>  // for INT_MAX

int main()
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
    int i, st = 0, tot = 0;

    for (i = 0; i < n; i++)
    {
        pid[i] = i + 1;
        printf("Enter arrival time for process %d: ", i + 1);
        scanf("%d", &at[i]);
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &bt[i]);
        k[i] = bt[i];  // Store original burst times
        f[i] = 0;  // Flag to check if the process is finished
        rt[i] = -1;  // Initialize response times to -1
    }

    while (true)
    {
        int min = INT_MAX, c = n;
        if (tot == n)
            break;

        for (i = 0; i < n; i++)
        {
            if (at[i] <= st && f[i] == 0 && bt[i] < min)
            {
                min = bt[i];
                c = i;
            }
        }

        if (c == n)
            st++;
        else
        {
            if (rt[c] == -1)
                rt[c] = st - at[c];  // Set response time when the process starts execution
            bt[c]--;
            st++;
            if (bt[c] == 0)
            {
                ct[c] = st;
                f[c] = 1;
                tot++;
            }
        }
    }

    for (i = 0; i < n; i++)
    {
        ta[i] = ct[i] - at[i];
        wt[i] = ta[i] - k[i];
    }

    printf("\nPid\tArrival\tBurst\tComplete\tTurn\tWaiting\tResponse\n");
    for (i = 0; i < n; i++)
    {
        printf("%d\t%d\t%d\t%d\t\t%d\t%d\t%d\n", pid[i], at[i], k[i], ct[i], ta[i], wt[i], rt[i]);
    }

    return 0;
}
