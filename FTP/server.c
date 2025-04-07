#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
int main(void)
{
    FILE *fp;
    int sockdesc,clientsock,clinet_size;
    struct sockaddr_in server_addr,client_addr;

    sockdesc = socket(AF_INET,SOCK_STREAM,0);
    if (sockdesc < 0)
    {
        printf("Can't create socket in server side\n");
        return -1;
    }
    printf("Socket Created Successfully\n");

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(2000);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if(bind(sockdesc,(struct sockaddr*)&server_addr,sizeof(server_addr))<0)
    {
        printf("Can't bind with the network\n");
        return -1;
    }
    printf("Done with Binding...\n");

    if(listen(sockdesc,1)<0)
    {
        printf("Couldn't listen\n");
        return -1;
    }
    printf("Listening......\n");

    clinet_size = sizeof(client_addr);
    clientsock = accept(sockdesc,(struct sockaddr*)&client_addr,&clinet_size);
    if(clientsock < 0)
    {
        printf("can't connect\n");
        return -1;
    }
    printf("Connect to IP: %s and port: %i\n",inet_ntoa(client_addr.sin_addr),ntohs(client_addr.sin_port));
    
    char fileread[100], rcv[100];
    int n;
    
    n=recv(clientsock,rcv,100,0);
    rcv[n]='\0';
    fp = fopen(rcv,"r");


    if(fp == NULL)
    {
        send(clientsock,"error",5,0);
        close(clientsock);
    }
    else
    {
        while(fgets(fileread,sizeof(fileread),fp))
        {
            if(send(clientsock,fileread,sizeof(fileread),0)<0)
            {
                printf("Can't send the content of file\n");
            }
            sleep(1);
        }
        if(!fgets(fileread,sizeof(fileread),fp))
        {
            printf("Done\n");
            send(clientsock,"completed",9,0);
        }
    }
    close(clientsock);
    close(sockdesc);
    return 0;
}