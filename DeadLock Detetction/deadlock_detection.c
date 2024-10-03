#include <stdio.h>

int main() {
    int n, m;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    printf("Enter the number of resource types: ");
    scanf("%d", &m);

    int alloc[n][m];
    int req[n][m];
    int total[m];
    int avail[m];

    // Taking total instances of each resource input
    printf("Enter the total instances of each resource:\n");
    for (int i = 0; i < m; i++) {
        printf("Resource %d: ", i + 1);
        scanf("%d", &total[i]);
    }

    // Taking allocation matrix input
    printf("Enter the allocation matrix:\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d allocation: ", i);
        for (int j = 0; j < m; j++) {
            scanf("%d", &alloc[i][j]);
        }
    }

    // Taking request matrix input
    printf("Enter the request matrix:\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d request: ", i);
        for (int j = 0; j < m; j++) {
            scanf("%d", &req[i][j]);
        }
    }

    int total_alloc[m];
    for (int i = 0; i < m; i++) {
        total_alloc[i] = 0;
    }

    // Calculating total allocated resources
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            total_alloc[j] += alloc[i][j];
        }
    }

    // Calculating available resources
    for (int i = 0; i < m; i++) {
        avail[i] = total[i] - total_alloc[i];
    }

    printf("Total Available Resources: ");
    for (int i = 0; i < m; i++) {
        printf("%d ", avail[i]);
    }
    printf("\n");

    printf("Total Allocated Resources: ");
    for (int i = 0; i < m; i++) {
        printf("%d ", total_alloc[i]);
    }
    printf("\n");

    int f[n], ans[n], ind = 0;
    for (int k = 0; k < n; k++) {
        f[k] = 0;
    }

    int deadlock = 0;
    for (int k = 0; k < n; k++) {
        printf("Iteration %d\n", k + 1);
        printf("Available Resources: [");
        for (int i = 0; i < m; i++) {
            printf("%d", avail[i]);
            if (i < m - 1) printf(",");
        }
        printf("]\n");

        int executed = 0;
        for (int i = 0; i < n; i++) {
            if (f[i] == 0) {
                int flag = 0;
                for (int j = 0; j < m; j++) {
                    if (req[i][j] > avail[j]) {
                        flag = 1;
                        break;
                    }
                }
                if (flag == 0) {
                    ans[ind++] = i;
                    printf("Process P%d can be executed\n", i);
                    for (int y = 0; y < m; y++) {
                        avail[y] += alloc[i][y];
                    }
                    f[i] = 1;
                    executed = 1;
                    break;
                }
            }
        }

        if (!executed) {
            deadlock = 1;
            printf("\nDeadlock found. Processes involved: ");
            for (int i = 0; i < n; i++) {
                if (f[i] == 0) {
                    printf("P%d ", i);
                }
            }
            printf("\n");
            break;
        }
    }

    if (deadlock == 0) {
        printf("\nNo Deadlock detected.\n");
    }

    return 0;
}
