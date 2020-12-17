/**
 * \file        manager.c
 * \brief       Gestion threads et sockets
 * */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <pthread.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdbool.h>

#include "manager.h"
#include "../buffer/read.h"
#include "../buffer/write.h"
#include "../config/parser.h"
#include "../packet/processor.h"

void openThread()
{
    pthread_t thread;
    pthread_create(&thread, 0, threadProcess, NULL);
    pthread_detach(thread);
}

void *threadProcess(void *ptr)
{
    char buffer_in[BUFFERSIZE];
    int sockfd = open_connection(); //*((int *)ptr);
    while (sockfd == -1)
    {
        sleep(1);
        sockfd = open_connection();
    }
    int len;
    setServerSocket(sockfd);
    while ((len = read(sockfd, buffer_in, BUFFERSIZE)) != 0)
    {
        if (len != -1)
        {
            printf("receive %d chars\n", len);
            printf("%.*s\n", len, buffer_in);
            Packet *receive_packet = BufferRead(buffer_in, BUFFERSIZE);
            memset(buffer_in, '\0', BUFFERSIZE);
            PacketProcessor(receive_packet);
        }
    }
    close(sockfd);
    printf("client pthread ended, len=%d\n", len);
}

int open_connection()
{
    int sockfd;
    parseConfig("client.ini");
    struct sockaddr_in serverAddr;

    // Create the socket.
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    //Configure settings of the server address
    // Address family is Internet
    serverAddr.sin_family = AF_INET;
    //Set port number, using htons function
    serverAddr.sin_port = htons(getServerPort());
    //Set IP address to localhost
    serverAddr.sin_addr.s_addr = inet_addr(getServerIpAddress());

    memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);

    //Connect the socket to the server using the address
    if (connect(sockfd, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) != 0)
    {
        //printf("Fail to connect to server");
        return -1;
        //exit(-1);
    };

    return sockfd;
}
