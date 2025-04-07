#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<stdlib.h>
int main(void)
{
    FILE *fp;
    int sockdesc;
    struct sockaddr_in server_addr;

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

    if(connect(sockdesc,(struct sockaddr*)&server_addr,sizeof(server_addr))<0)
    {
        printf("Can't connect with clinet\n");
        return -1;
    }
    printf("Connected to the server\n");

    int r;
    char fname[50],sname[50],recvmsg[50];
    printf("Enter the name of the file to open:");
    scanf("%s",fname);
    printf("\nEnter the name of the file to store:");
    scanf("%s",sname);
    fp = fopen(sname,"w");

    send(sockdesc,fname,sizeof(fname),0);


    while(1)
    {
        r=recv(sockdesc,recvmsg,100,0);
        recvmsg[r]='\0';

        if (strcmp(recvmsg,"error")==0)
        {
            printf("\nFile does not exist");
            exit(1);
        }
        if(strcmp(recvmsg,"completed")==0)
        {
            printf("\nFile transferred completed....\n");
            fclose(fp);
            break;
        }
        else
        {
            fputs("recvmsg",stdout);
            fprintf(fp,"%s",recvmsg);
        }
    }
    close(sockdesc);
    return 0;
}