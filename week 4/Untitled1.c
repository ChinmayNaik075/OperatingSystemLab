#include <stdio.h>
#include <math.h>

#define MAX 10

typedef struct {
    int id;
    float C, T;
    int remaining;
    int next_arrival;
    int deadline;
    int weight;
} Task;

int main() {
    int n, time_limit;
    float U = 0, bound;

    printf("Enter number of tasks: ");
    scanf("%d", &n);

    Task t[MAX];

    // INPUT
    for (int i = 0; i < n; i++) {
        printf("\nTask %d:\n", i + 1);
        printf("Execution time (C): ");
        scanf("%f", &t[i].C);
        printf("Period (T): ");
        scanf("%f", &t[i].T);

        t[i].id = i + 1;
        t[i].remaining = 0;
        t[i].next_arrival = 0;
        t[i].deadline = 0;
        t[i].weight = i + 1;   // simple weights
        U += (t[i].C / t[i].T);
    }

    // ===== RMS PART =====
    bound = n * (pow(2, 1.0 / n) - 1);

    printf("\n===== RMS =====\n");
    printf("CPU Utilization = %.4f\n", U);
    printf("Bound = %.4f\n", bound);

    if (U <= bound)
        printf("Schedulable using RMS\n");
    else
        printf("Not guaranteed schedulable\n");

    printf("\nEnter simulation time: ");
    scanf("%d", &time_limit);

    printf("\nRMS Gantt Chart:\n|");

    // RESET
    for (int i = 0; i < n; i++) {
        t[i].remaining = 0;
        t[i].next_arrival = 0;
    }

    for (int time = 0; time < time_limit; time++) {

        // arrivals
        for (int i = 0; i < n; i++) {
            if (time == t[i].next_arrival) {
                t[i].remaining = (int)t[i].C;
                t[i].next_arrival += (int)t[i].T;
            }
        }

        // choose smallest period
        int highest = -1;
        for (int i = 0; i < n; i++) {
            if (t[i].remaining > 0) {
                if (highest == -1 || t[i].T < t[highest].T)
                    highest = i;
            }
        }

        if (highest != -1) {
            printf(" T%d |", t[highest].id);
            t[highest].remaining--;
        } else {
            printf(" Idle |");
        }
    }

    printf("\n0");
    for (int i = 1; i <= time_limit; i++) {
        printf("%6d", i);
    }

    printf("\n\n");

    // ===== EDF PART =====
    printf("===== EDF =====\n");
    printf("Gantt Chart:\n|");

    // RESET
    for (int i = 0; i < n; i++) {
        t[i].remaining = 0;
        t[i].next_arrival = 0;
        t[i].deadline = 0;
    }

    for (int time = 0; time < time_limit; time++) {

        // arrivals
        for (int i = 0; i < n; i++) {
            if (time == t[i].next_arrival) {
                t[i].remaining = (int)t[i].C;
                t[i].deadline = time + (int)t[i].T;
                t[i].next_arrival += (int)t[i].T;
            }
        }

        // choose earliest deadline
        int chosen = -1;
        for (int i = 0; i < n; i++) {
            if (t[i].remaining > 0) {
                if (chosen == -1 || t[i].deadline < t[chosen].deadline)
                    chosen = i;
            }
        }

        if (chosen != -1) {
            printf(" T%d |", t[chosen].id);
            t[chosen].remaining--;
        } else {
            printf(" Idle |");
        }
    }

    printf("\n0");
    for (int i = 1; i <= time_limit; i++) {
        printf("%6d", i);
    }

    printf("\n\n");

    // ===== PROPORTIONAL SHARE =====
    printf("===== Proportional Share Scheduling =====\n");

    int total_weight = 0;
    for (int i = 0; i < n; i++) {
        total_weight += t[i].weight;
        t[i].remaining = (int)t[i].C;
    }

    printf("Execution Order:\n");

    int time = 0;
    while (1) {
        int done = 1;

        for (int i = 0; i < n; i++) {
            if (t[i].remaining > 0) {
                done = 0;

                int slice = (t[i].weight * time_limit) / total_weight;
                if (slice <= 0) slice = 1;

                printf("T%d for %d units\n", t[i].id, slice);

                if (slice > t[i].remaining)
                    slice = t[i].remaining;

                t[i].remaining -= slice;
                time += slice;
            }
        }

        if (done) break;
    }

    return 0;
}
