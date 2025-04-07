#include<stdio.h>

struct node 
{
    unsigned dist[200];
    unsigned from[200];
}rt[10];

int main()
{
    int i,j,n,k,count=0;
    int costmat[20][20];

    printf("Enter the no.of nodes:");
    scanf("%d",&n);
    printf("\nEnter the cost matrix:\n");
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            scanf("%d",&costmat[i][j]);
            if (i == j){costmat[i][i]=0;}
            rt[i].dist[j]=costmat[i][j];
            rt[i].from[j]=j;
        }
    }

    do
    {
        count = 0;
        for(i=0;i<n;i++)
        {
            for(j=0;j<n;j++)
            {
                for(k=0;k<n;k++)
                {
                    if(rt[i].dist[j]>costmat[i][k] + rt[k].dist[j])
                    {
                        rt[i].dist[j] = rt[i].dist[k] + rt[k].dist[j];
                        rt[i].from[j] = k;
                        count++;
                    }
                }
            }
        }
    } while (count!=0);
    

    for(i=0;i<n;i++)
    {
        printf("\nROUTING TABLE for %dst router\n",i+1);
        for(j=0;j<n;j++)
        {
            printf("node %d from %d -> Distance is %d\n",j+1,rt[i].from[j]+1,rt[i].dist[j]);
        }
    }
    printf("\n\n");
    return 0;
}