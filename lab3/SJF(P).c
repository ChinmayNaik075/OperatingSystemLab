#include <stdio.h>

int main()
{
    int n,i;
    int at[20], bt[20], rt[20], wt[20], tat[20], ct[20];

    int time=0, completed=0, min, idx;
    float awt=0, atat=0;

    printf("Enter number of processes: ");
    scanf("%d",&n);

    for(i=0;i<n;i++)
    {
        printf("Enter Arrival Time of P%d: ",i+1);
        scanf("%d",&at[i]);

        printf("Enter Burst Time of P%d: ",i+1);
        scanf("%d",&bt[i]);

        rt[i]=bt[i];
    }

    while(completed<n)
    {
        min=9999;
        idx=-1;

        for(i=0;i<n;i++)
        {
            if(at[i]<=time && rt[i]>0 && rt[i]<min)
            {
                min=rt[i];
                idx=i;
            }
        }

        if(idx==-1)
        {
            time++;
            continue;
        }

        rt[idx]--;
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

    printf("\nP\tAT\tBT\tCT\tWT\tTAT\n");

    for(i=0;i<n;i++)
    {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
        i+1,at[i],bt[i],ct[i],wt[i],tat[i]);
    }

    printf("\nAverage Waiting Time = %.2f",awt/n);
    printf("\nAverage Turnaround Time = %.2f",atat/n);

    return 0;
}