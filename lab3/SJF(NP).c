#include <stdio.h>

int main()
{
    int n, i, j;
    int at[20], bt[20], wt[20], tat[20], ct[20], completed[20]={0};
    int time=0, done=0, min, idx;

    float awt=0, atat=0;

    printf("Enter number of processes: ");
    scanf("%d",&n);

    for(i=0;i<n;i++)
    {
        printf("Enter Arrival Time of P%d: ",i+1);
        scanf("%d",&at[i]);

        printf("Enter Burst Time of P%d: ",i+1);
        scanf("%d",&bt[i]);
    }

    while(done<n)
    {
        min=9999;
        idx=-1;

        for(i=0;i<n;i++)
        {
            if(at[i]<=time && completed[i]==0 && bt[i]<min)
            {
                min=bt[i];
                idx=i;
            }
        }

        if(idx==-1)
        {
            time++;
        }
        else
        {
            ct[idx]=time+bt[idx];
            tat[idx]=ct[idx]-at[idx];
            wt[idx]=tat[idx]-bt[idx];

            time=ct[idx];
            completed[idx]=1;
            done++;
        }
    }

    printf("\nP\tAT\tBT\tCT\tWT\tTAT\n");

    for(i=0;i<n;i++)
    {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
        i+1,at[i],bt[i],ct[i],wt[i],tat[i]);

        awt+=wt[i];
        atat+=tat[i];
    }

    printf("\nAverage Waiting Time = %.2f",awt/n);
    printf("\nAverage Turnaround Time = %.2f",atat/n);

    return 0;
}