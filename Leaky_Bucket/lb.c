#include<stdio.h>
int main()
{
    int bsize,n,out,in,bucket=0;
    printf("Enter the BucketSize:");
    scanf("%d",&bsize);
    printf("Enter the no.of input:");
    scanf("%d",&n);
    printf("Outgoing rate:");
    scanf("%d",&out);

    while (n!=0)
    {
        printf("Enter the incomeing packet rate:");
        scanf("%d",&in);
        if(in<=(bsize-bucket))
        {
            bucket=bucket+in;
            printf("Bucket contain %d out of %d:\n",bucket,bsize);
        }
        else
        {
            printf("Packet Dropped %d:\n",in-(bsize-bucket));
            bucket=bsize;
            printf("Bucket contain %d out of %d:\n",bucket,bsize);
        }
        bucket=bucket-out;
        printf("After outgoing,Bucket contain %d out of %d:\n",bucket,bsize);
        n--;
        printf("\n\n");
    }
    
}