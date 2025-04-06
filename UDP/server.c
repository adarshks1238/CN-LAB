#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
int main(void)
{
    int sockdesc;
    struct sockaddr_in server_addr,client_addr;
    int client_size=sizeof(client_addr);
    char server_message[5000],client_message[5000];
    memset(server_message,'\0',sizeof(server_message));
    memset(client_message,'\0',sizeof(client_message));

    sockdesc = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
    if(sockdesc < 0)
    {
        printf("Cant Create socket in server side\n");
        return -1;
    }
    printf("Socket Created successfully\n");


    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(2000);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if(bind(sockdesc,(struct sockaddr*)&server_addr,sizeof(server_addr))<0)
    {
        printf("Can't bind\n");
        return -1;
    }
    printf("Done with binding\nListen for the message......\n");

    if(recvfrom(sockdesc,client_message,sizeof(client_message),0,(struct sockaddr*)&client_addr,&client_size)<0)
    {
        printf("Can't receive from client\n");
        return -1;
    }
    printf("Client IP %s and Port %i\n",inet_ntoa(client_addr.sin_addr),ntohs(client_addr.sin_port));
    printf("Message of client side is %s\n",client_message);

    printf("Enter the message to clinet:");
    fgets(server_message,sizeof(server_message),stdin);

    if(sendto(sockdesc,server_message,sizeof(server_message),0,(struct sockaddr*)&client_addr,client_size)<0)
    {
        printf("\nCant Send message to client ");
        return -1;
    }

    close(sockdesc);
    return 0;
}
