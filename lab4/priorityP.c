#include <stdio.h>

int main()
{
    int n,i;
    int at[20], bt[20], rt[20], pr[20];
    int ct[20], wt[20], tat[20];

    int time=0, completed=0;
    int highest, idx;

    float awt=0, atat=0;

    printf("Enter number of processes: ");
    scanf("%d",&n);

    for(i=0;i<n;i++)
    {
        printf("\nProcess P%d\n",i+1);

        printf("Arrival Time: ");
        scanf("%d",&at[i]);

        printf("Burst Time: ");
        scanf("%d",&bt[i]);

        printf("Priority: ");
        scanf("%d",&pr[i]);

        rt[i]=bt[i];   // remaining time
    }

    while(completed<n)
    {
        highest=9999;
        idx=-1;

        for(i=0;i<n;i++)
        {
            if(at[i]<=time && rt[i]>0 && pr[i]<highest)
            {
                highest=pr[i];
                idx=i;
            }
        }

        if(idx==-1)
        {
            time++;
            continue;
        }

        rt[idx]--;   // execute process for 1 unit
        time++;

        if(rt[idx]==0)
        {
            completed++;

            ct[idx]=time;
            tat[idx]=ct[idx]-at[idx];
            wt[idx]=tat[idx]-bt[idx];

            awt+=wt[idx];
            atat+=tat[idx];
        }
    }

    printf("\nP\tAT\tBT\tPR\tCT\tWT\tTAT\n");

    for(i=0;i<n;i++)
    {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
        i+1,at[i],bt[i],pr[i],ct[i],wt[i],tat[i]);
    }

    printf("\nAverage Waiting Time = %.2f",awt/n);
    printf("\nAverage Turnaround Time = %.2f",atat/n);

    return 0;
}
