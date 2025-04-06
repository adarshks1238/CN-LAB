#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
int main(void)
{
    int sockdesc;
    struct sockaddr_in server_addr;
    char server_message[5000],client_message[5000];
    int server_size = sizeof(server_addr);
    memset(server_message,'\0',sizeof(server_message));
    memset(client_message,'\0',sizeof(client_message));

    sockdesc = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
    if(sockdesc < 0)
    {
        printf("Cant Create socket in client side\n");
        return -1;
    }
    printf("Socket Created successfully\n");


    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(2000);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    printf("Enter the message for server:");
    fgets(client_message,sizeof(client_message),stdin);

    if(sendto(sockdesc,client_message,strlen(client_message),0,(struct sockaddr*)&server_addr,server_size)<0)
    {
        printf("\nCan't send message to server side");
        return -1;
    }
    if(recvfrom(sockdesc,server_message,sizeof(server_message),0,NULL,NULL)<0)
    {
        printf("\nCan't receive message from server");
        return -1;
    }
    printf("\nMessage from server side is %s",server_message);

    close(sockdesc);

    return 0;
}