#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<stdlib.h>
int main(void)
{
    int sockdesc;
    struct sockaddr_in server_addr;

    sockdesc = socket(AF_INET,SOCK_STREAM,0);
    if (sockdesc < 0)
    {
        printf("can't create socket\n");
        return -1;
    }
    printf("Socket Created Successfully in client side\n");

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(2000);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");


    if (connect(sockdesc,(struct sockaddr*)&server_addr,sizeof(server_addr))<0)
    {
        printf("Can't connect to the network\n");
        return -1;
    }
    printf("Connected to the network\n");

    int k=5,m=1,d;
    char buffer[1024];
    while (k!=0)
    {
        if(m<=5)
        {
            printf("Sending frame is %d\n",m);
        }
        if(m%2==0)
        {
            strcpy(buffer,"frame");
        }
        else
        {
            strcpy(buffer,"error");
            printf("Packet lossed\n");
            for(d=0;d<3;d++)
            {
                printf("Waiting for %d sec\n",d);
            }
            printf("Retransmitting....\n");
            strcpy(buffer,"frame");
            sleep(3);
        }
        int y = send(sockdesc,buffer,19,0);
        if(y < 0)
        {
            printf("Error while sending\n");
            exit(1);
        }
        printf("Frame %d send\n",m);
        int z = recv(sockdesc,buffer,1024,0);
        if (z < 0)
        {
            printf("Error while receving\n");
            exit(1);
        }
        if (strncmp(buffer,"ack",3)==0)
        {
            printf("Received ack from %dth frame\n",m);
        }
        k--;
        m++;
    }
    close(sockdesc);
    return 0;
}