#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<netdb.h>
#include<time.h>
#include<sys/time.h>
struct timeval timeout;

    void serfun(int sockfd, int nf, int ws)
    {
        timeout.tv_sec = 3;
        timeout.tv_usec = 0;
        char buff[80];
        int ack, i = 0, n, k, w1 = 0, w2 = ws - 1, j, flag = 0;
        if (setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, (const char *)&timeout, sizeof(timeout)) < 0)
            perror("setsockopt(SO_RCVTIMEO) failed");
    
        for (i = 0; i < nf && i <= w2; i++)
        {
            bzero(buff, sizeof(buff));
            snprintf(buff, sizeof(buff), "%d", i);
            k = send(sockfd, buff, sizeof(buff), 0);
            printf("Frame %d sent\n", i);
        }
        while (1)
        {
            if (w2 - w1 != ws - 1 && flag == 0 && i != nf)
            {
                bzero(buff, sizeof(buff));
                snprintf(buff, sizeof(buff), "%d", i);
                k = send(sockfd, buff, sizeof(buff), 0);
                printf("Frame %d sent\n", i);
                w2++;
                i++;
            }
            flag = 0;
            bzero(buff, sizeof(buff));
            n = recv(sockfd, buff, 80, 0);
            ack = atoi(buff);
            if (n > 0)
            {
                if (ack + 1 == nf)
                {
                    printf("Acknowlegement received: %d\nExit\n", ack);
                    bzero(buff, sizeof(buff));
                    strcpy(buff, "Exit");
                    k = send(sockfd, buff, sizeof(buff), 0);
                    break;
                }
                if (ack == w1)
                {
                    w1++;
                    printf("Acknowlegement received: %d\n", ack);
                }
            }
            else
            {
                printf("Acknowledgement not received for %d\nResending frames\n", w1);
                for (j = w1; j < nf && j < w1 + ws; j++)
                {
                    bzero(buff, sizeof(buff));
                    snprintf(buff, sizeof(buff), "%d", j);
                    k = send(sockfd, buff, sizeof(buff), 0);
                    printf("Frame %d sent\n", j);
                }
                flag = 1;
            }
        }
    }
int main(void)
{
    int sockdesc;
    struct sockaddr_in server_addr;

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

   
    if (connect(sockdesc,(struct sockaddr*)&server_addr,sizeof(server_addr))<0)
    {
        printf("Cannot Connect\n");
        exit(0);
    }
    printf("Connected successfully with server\n");

    int f,w;
    printf("Enter no.of frames:");
    scanf("%d",&f);
    printf("\nEnter the window size:");
    scanf("%d",&w);

    serfun(sockdesc,f,w);

    close(sockdesc);

    return 0;
}