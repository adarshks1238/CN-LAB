#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
int main(void)
{
    int sockdesc,client_sock,clientsize;
    struct sockaddr_in server_addr,client_addr;
    
    char server_message[5000],client_message[500];

    memset(server_message,'\0',sizeof(server_message));
    memset(client_message,'\0',sizeof(client_message));

    sockdesc = socket(AF_INET,SOCK_STREAM,0);
    if(sockdesc<0)
    {
        printf("Error to create socket\n");
        return -1;
    }
    printf("Socket Created Successfully... \n");

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(2000);
    server_addr.sin_addr.s_addr= inet_addr("127.0.0.1");

    if(bind(sockdesc,(struct sockaddr*)&server_addr,sizeof(server_addr))<0)
    {
        printf("Error while Binding\n");
        return -1;
    }
    printf("Done with binding\n");

    if(listen(sockdesc , 1)<0)
    {
        printf("Can't Listen\n");
        return -1;
    }
    printf("Listening...........\n");

    clientsize = sizeof(client_addr);
    client_sock = accept(sockdesc ,(struct sockaddr*)&client_addr,&clientsize);
    if(client_sock < 0)
    {
        printf("Cant accept\n");
        return -1;
    }
    printf("Client Connected at IP:%s port %i\n",inet_ntoa(client_addr.sin_addr),ntohs(client_addr.sin_port));

    if(recv(client_sock,client_message,sizeof(client_message),0)<0)
    {
        printf("Can't recevie server's Message\n");
        return -1;
    }
    printf("Message from client is %s",client_message);

    printf("Enter the message to client:");
    fgets(server_message,sizeof(server_message),stdin);

    if(send(client_sock,server_message,sizeof(server_message),0)<0)
    {
        printf("Error while sending message\n");
        return -1;
    }

    close(client_sock);
    close(sockdesc);
    return 0;
}