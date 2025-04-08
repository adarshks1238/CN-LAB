#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<netdb.h>
#include<time.h>
#include<sys/time.h>
struct timeval timeout;

void serfun(int sockdesc,int frame,int window)
{
    timeout.tv_sec = 3;
    timeout.tv_usec = 0;

    char buffer[50];
    int ack,ws=0,we=window-1,i,j,n,k;
    if( setsockopt(sockdesc, SOL_SOCKET, SO_RCVTIMEO, (const char*)&timeout, sizeof(timeout))<0)
    {
        perror("setsokopt failed");
    }

    for(i=0; i<frame && i<we;i++)
    {
        bzero(buffer,sizeof(buffer));
        snprintf(buffer,sizeof(buffer),"%d",i);
        k = send(sockdesc,buffer,sizeof(buffer),0);
        printf("\nframe %d send",i);
    }
}

int main(void)
{
    int sockdesc;
    struct sockaddr_in server_addr;

    sockdesc = socket(AF_INET,SOCK_STREAM,0);
    if(sockdesc < 0)
    {
        printf("Can't Create Socket\n");
        exit(0);
    }
    printf("Socket created Successfully\n");

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(2000);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

   
    if (connect(sockdesc,(struct sockaddr*)&server_addr,sizeof(server_addr))<0)
    {
        printf("Cannot Connect\n");
        exit(0);
    }
    printf("Connected successfully with server\n");

    int f,w;
    printf("Enter no.of frames:");
    scanf("%d",&f);
    printf("\nEnter the window size:");
    scanf("%d",&w);

    serfun(sockdesc,f,w);

    close(sockdesc);

    return 0;
}