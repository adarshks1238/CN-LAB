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
    return 0;
}