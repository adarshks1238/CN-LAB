#include<stdio.h>
#include<string.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<unistd.h>
int main(void)
{
    int sockdesc;
    struct sockaddr_in server_addr;
    char server_message[5000],client_message[500];

    memset(server_message,'\0',sizeof(server_message));
    memset(client_message,'\0',sizeof(client_message));

    sockdesc = socket(AF_INET,SOCK_STREAM,0);
    if(sockdesc < 0)
    {
        printf("Can't Create Socket\n");
        return -1;
    }
    printf("Socket Created Successfully\n");

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(2000);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if(connect(sockdesc, (struct sockaddr*)&server_addr,sizeof(server_addr))<0)
    {
        printf("Can't Connect to server\n");
        return -1;
    }
    printf("Connected with server successfully\n");

    printf("Enter the message to server:");
    fgets(client_message,sizeof(client_message),stdin);

    if(send(sockdesc,client_message,strlen(client_message),0)<0)
    {
        printf("Error while sending message\n");
        return -1;
    }
    
    if(recv(sockdesc,server_message,sizeof(server_message),0)<0)
    {
        printf("Can't recevie server's Message");
        return -1;
    }
    printf("Message from server is %s",server_message);

    close(sockdesc);
    return 0;
}