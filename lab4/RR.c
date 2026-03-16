#include <stdio.h>

int main()
{
    int n, tq;
    int at[20], bt[20], rt[20];
    int ct[20], wt[20], tat[20];

    int rq[100];        // ready queue
    int front = 0, rear = 0;

    int visited[20] = {0};

    int time = 0, completed = 0;

    float awt = 0, atat = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for(int i=0;i<n;i++)
    {
        printf("Enter AT for P%d: ", i+1);
        scanf("%d",&at[i]);

        printf("Enter BT for P%d: ", i+1);
        scanf("%d",&bt[i]);

        rt[i] = bt[i];
    }

    printf("Enter Time Quantum: ");
    scanf("%d",&tq);

    // insert first arriving process
    rq[rear++] = 0;
    visited[0] = 1;

    while(front < rear)
    {
        int i = rq[front++];

        if(rt[i] > tq)
        {
            time += tq;
            rt[i] -= tq;
        }
        else
        {
            time += rt[i];
            rt[i] = 0;

            ct[i] = time;
            completed++;

            tat[i] = ct[i] - at[i];
            wt[i] = tat[i] - bt[i];

            awt += wt[i];
            atat += tat[i];
        }

        // add newly arrived processes
        for(int j=0;j<n;j++)
        {
            if(at[j] <= time && visited[j]==0)
            {
                rq[rear++] = j;
                visited[j] = 1;
            }
        }

        // if process not finished, push back to queue
        if(rt[i] > 0)
        {
            rq[rear++] = i;
        }
    }

    printf("\nP\tAT\tBT\tCT\tWT\tTAT\n");

    for(int i=0;i<n;i++)
    {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
        i+1, at[i], bt[i], ct[i], wt[i], tat[i]);
    }

    printf("\nAverage WT = %.2f", awt/n);
    printf("\nAverage TAT = %.2f\n", atat/n);

    return 0;
}