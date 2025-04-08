#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<netdb.h>
void serfun(int clientsock)
{
    char buffer[50];

    int f,c,ack,next = 0;
    while(1)
    {
        sleep(1);
        bzero(buffer,50);
        recv(clientsock,buffer,50,0);
        if(strcmp("Exit",buffer)==0)
        {
            printf("Exit\n");
            break;
        }
        f = atoi(buffer);

        if (f!=next)
        {
            printf("frame discard: %d\n",f);
            printf("Acknowledgment sent : %d",ack);
            bzero(buffer,50);
            snprintf(buffer,sizeof(buffer),"%d",ack);
            send(clientsock,buffer,sizeof(buffer),0);
            continue;
        }
        c=rand() % 3;
        switch(c)
        {
            case 1:
                sleep(2);
                ack = f;
                printf("Frame Received %d\n",f);
                printf("Acknowlegment send %d\n",ack);
                bzero(buffer,50);
                snprintf(buffer,sizeof(buffer),"%d",ack);
                send(clientsock,buffer,sizeof(buffer),0);
                next = ack+1;
                break;
            case 2:
                ack = f;
                printf("Frame Received %d\n",f);
                printf("Acknowlegment send %d\n",ack);
                bzero(buffer,50);
                snprintf(buffer,sizeof(buffer),"%d",ack);
                send(clientsock,buffer,sizeof(buffer),0);
                next = ack+1;
                break;
        }
    }
}
int main(void)
{
    
    int sockdesc,clientsock,client_size;
    struct sockaddr_in server_addr,client_addr;

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

    if (bind(sockdesc,(struct sockaddr*)&server_addr,sizeof(server_addr))<0)
    {
        printf("Couldn't Bind\n");
        exit(0);
    }
    printf("Done With Binding\n");

    if(listen(sockdesc,1)<0)
    {
        printf("Couldn't Listen\n");
        exit(0);
    }
    printf("Listening.............\n");

    client_size = sizeof(client_addr);
    clientsock = accept(sockdesc,(struct sockaddr*)&client_addr,&client_size);
    if(clientsock < 0)
    {
        printf("Can't accept\n");
        exit(0);
    }
    printf("Connected Successfully with client\n");
    
    serfun(clientsock);
    close(sockdesc);

    return 0;
}