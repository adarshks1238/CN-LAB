#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<netdb.h>
void serfun(int connfd)
{
    char buff[80];
    int f, c, ack, next = 0;
    while (1)
    {
        sleep(1);
        bzero(buff, 80);
        recv(connfd, buff, 80, 0);
        if (strcmp("Exit", buff) == 0)
        {
            printf("Exit\n");
            break;
        }
        f = atoi(buff);
        if (f != next)
        {
            printf("Frame %d discarded\nAcknowledgement sent: %d\n", f, ack);
            bzero(buff, 80);
            snprintf(buff, sizeof(buff), "%d", ack);
            send(connfd, buff, sizeof(buff), 0);
            continue;
        }
        c = rand() % 3;
        switch (c)
        {
            case 0:
                break;
            case 1:
                ack = f;
                sleep(2);
                printf("Frame %d received\nAcknowledement sent: %d\n", f, ack);
                bzero(buff, 80);
                snprintf(buff, sizeof(buff), "%d", ack);
                send(connfd, buff, sizeof(buff), 0);
                next = ack + 1;
                break;
            case 2:
                ack = f;
                printf("Frame %d received\nAcknowledement sent: %d\n", f, ack);
                bzero(buff, 80);
                snprintf(buff, sizeof(buff), "%d", ack);
                send(connfd, buff, sizeof(buff), 0);
                next = ack + 1;
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