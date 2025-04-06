#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<stdlib.h>
int main(void)
{
    int sockdesc,clientsock,client_size;
    struct sockaddr_in server_addr,client_addr;

    sockdesc = socket(AF_INET,SOCK_STREAM,0);
    if (sockdesc < 0)
    {
        printf("can't create socket\n");
        return -1;
    }
    printf("Socket Created Successfully in server side\n");

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(2000);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (bind(sockdesc,(struct sockaddr*)&server_addr,sizeof(server_addr))<0)
    {
        printf("Can't bind with client\n");
        return -1;
    }
    printf("Done with binding\n");

    if(listen(sockdesc,1)<0)
    {
        printf("Can't listen\n");
        return -1;
    }
    printf("Listening......\n");

    client_size = sizeof(client_addr);
    clientsock = accept(sockdesc,(struct sockaddr*)&client_addr,&client_size);
    if (clientsock < 0)
    {
        printf("Can't accpet\n");
        return -1;
    }
    printf("connected to the IP: %s and Port:%i\n",inet_ntoa(client_addr.sin_addr),ntohs(client_addr.sin_port));


    int k=5,m=1,d;
    char buffer[1024];
    while (k!=0)
    {
        int y= recv(clientsock,buffer,1024,0);
        if(y<0){
            printf("Error while receving\n");
            exit(1);
        }
        if (strncmp(buffer,"frame",5)==0)
        {
            printf("Frame %d recv\n",m);
        }
        else
        {
            printf("Frame not recv\n");
        }
        if(m%2==0)
        {
            strcpy(buffer,"ack");
        }
        else
        {
            strcpy(buffer,"cak");
            printf("Ack lost\n");
            for(d=0;d<3;d++)
            {
                printf("Waiting for %d sec\n",d);
            }
            printf("Retransmitting ack.......\n");
            strcpy(buffer,"ack");
        }
        printf("sending ack for frame %d\n",m);
        int z = send (clientsock,buffer,19,0);
        if (z < 0)
        {
            printf("Can't send ack\n");
            exit(1);
        }
        
        k--;
        m++;
    }
    return 0;

}