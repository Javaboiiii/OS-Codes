#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int pid;  // Process ID
    int bt;   // Burst Time
    int at;   // Arrival Time
    int rt;   // Remaining Time
    int ft;   // Finish Time
    int tat;  // Turn Around Time
    int wt;   // Waiting Time
} Process;

// Sort processes based on arrival time and then burst time if arrival times are the same
void sort(int n, Process p[n]) {
    int i, j;
    Process temp;

    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - 1 - i; j++) {
            if ((p[j].at > p[j + 1].at) || ((p[j].at == p[j + 1].at) && (p[j].bt > p[j + 1].bt))) {
                temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }
}

// Calculate the total number of iterations required for the Gantt chart
int countIteration(int n, Process p[n], int tq) {
    int i, total_iterations = 0;
    for (i = 0; i < n; i++) {
        total_iterations += (p[i].bt + tq - 1) / tq;  // Calculate ceiling of bt/tq
    }
    return total_iterations;
}

// Print the Gantt chart for process execution
void print_chart(int n, Process p[n]) {
    int i, j;
    printf("\n\t+");
    for (i = 0; i < n; i++) {
        for (j = 1; j <= p[i].bt; j++)
            printf("---");
        printf("+");
    }
    printf("\n\t|");
    for (i = 0; i < n; i++) {
        printf(" P%d", p[i].pid);
        for (j = 1; j < p[i].bt; j++)
            printf("   ");
        printf("|");
    }
    printf("\n\t+");
    for (i = 0; i < n; i++) {
        for (j = 1; j <= p[i].bt; j++)
            printf("---");
        printf("+");
    }

    int check = 0;
    printf("\n\t%d", p[0].at);
    if (p[0].at > 9)
        check = 1;
    for (i = 0; i < n; i++) {
        for (j = 1; j <= p[i].bt; j++)
            if (check == 1) {
                printf("  ");
                check = 0;
            } else {
                printf("   ");
            }
        printf("%d", p[i].ft);
        if (p[i].ft > 9)
            check = 1;
    }
}

// Execute processes using Round Robin scheduling
int execute(int n, Process p[n], int total_iterations, Process exec[total_iterations], int start_time, int tq) {
    int i, j;
    int t = start_time;  // Initialize current time to start time
    j = 0;

    for (i = 0; i < total_iterations; i++) {
        // Find the next process that still has remaining time
        while (p[j].rt == 0) {
            j = (j + 1) % n;
        }

        // Execute the current process
        exec[i] = p[j];
        if (p[j].rt <= tq) {
            t += p[j].rt;
            exec[i].bt = p[j].rt;
            p[j].rt = 0;
            p[j].ft = t;
        } else {
            t += tq;
            p[j].rt -= tq;
            exec[i].bt = tq;
        }
        exec[i].ft = t;
        exec[i].rt = p[j].rt;

        j = (j + 1) % n;  // Move to the next process
    }
    return t;
}

// Print the process table with computed metrics
void print_table(int n, Process p[n]) {
    int i;
    float total_wt = 0, total_tat = 0;
    printf("\n\n\tpid\tAt\tBt\tFt\tTAt\tWt\n");
    for (i = 0; i < n; i++) {
        p[i].tat = p[i].ft - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;
        total_wt += p[i].wt;
        total_tat += p[i].tat;
        printf("\t%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].at, p[i].bt, p[i].ft, p[i].tat, p[i].wt);
    }
    printf("\n\tAverage waiting time: %.2f units\n\tAverage turn-around time: %.2f units", total_wt / n, total_tat / n);
}

int main() {
    int n, i, t = 0, tq;
    printf("\n\t\t\t\tRound Robin\n\n\tEnter the total number of processes: ");
    scanf("%d", &n);
    Process p[n];

    printf("\n\tEnter the time quantum: ");
    scanf("%d", &tq);

    printf("\n\tEnter the following data for each process: ");
    for (i = 0; i < n; i++) {
        printf("\n\tProcess %d:\n\tArrival time: ", i + 1);
        scanf("%d", &p[i].at);
        printf("\tBurst time: ");
        scanf("%d", &p[i].bt);
        p[i].rt = p[i].bt;
        p[i].pid = i + 1;
    }
    sort(n, p);  // Sort processes by arrival time and burst time

    int total_iterations = countIteration(n, p, tq);  // Calculate total iterations for the Gantt chart
    Process exec[total_iterations];

    t = execute(n, p, total_iterations, exec, t, tq);  // Execute processes

    print_table(n, p);  // Print process table
    printf("\n\n\tGantt chart\n");
    print_chart(total_iterations, exec);  // Print Gantt chart

    return 0;
}
