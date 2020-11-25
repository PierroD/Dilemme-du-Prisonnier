#include <arpa/inet.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "srvcxnmanager.h"
#include "utils/configreader.h"
#include "utils/bufferreader.h"
#include "models/player.h"
#include "models/room.h"

connection_t *connections[MAXSIMULTANEOUSCLIENTS];
Config configfile;

void init_sockets_array()
{
    for (int i = 0; i < getMaxSimultaneousConnection(); i++)
    {
        connections[i] = NULL;
    }
}

void del(connection_t *connection)
{
    for (int i = 0; i < getMaxSimultaneousConnection(); i++)
    {
        if (connections[i] == connection)
        {
            connections[i] = NULL;
            return;
        }
    }
    perror("Connection not in pool ");
    exit(-5);
}



/**
 * Thread allowing server to handle multiple client connections
 * @param ptr connection_t 
 * @return 
 */
void *threadProcess(void *ptr)
{
    char buffer_in[BUFFERSIZE];
    char buffer_out[BUFFERSIZE];
    int len;
    connection_t *connection;
    if (!ptr)
        pthread_exit(0);
    connection = (connection_t *)ptr;
    printf("New incoming connection \n");

    Player *current_player = create_player(connection);
    Room *current_room = configureRoom(current_player);

    PlayerIsConnected(current_player);
    // Ask if the player is ready
    sprintf(buffer_out, "Are you ready #%i ? \n", current_player->connection->index);
    write(current_player->connection->sockfd, buffer_out, strlen(buffer_out));

    while ((len = read(current_player->connection->sockfd, buffer_in, BUFFERSIZE)) > 0)
    {
        
        read_buffer(current_room,current_player, buffer_in, BUFFERSIZE);

        if (strncmp(buffer_in, "bye", 3) == 0)
        {
            break;
        }

        /*#if DEBUG
        printf("DEBUG-----------------------------------------------------------\n");
        printf("len : %i\n", len);
        printf("Buffer : %.*s\n", len, buffer_in);
        printf("----------------------------------------------------------------\n");
        #endif*/
        // strcpy(buffer_out, "\nServer Echo : ");
        // strncat(buffer_out, buffer_in, len);

        // if (buffer_in[0] == '@')
        // { // envoie à tous les joueurs de la salle
        //     for (int i = 0; i < current_room->nb_player; i++)
        //     {
        //         if (current_room->players[i].connection != NULL)
        //         {
        //             write(current_room->players[i].connection->sockfd, buffer_out, strlen(buffer_out));
        //         }
        //     }
        // }
        // else if (buffer_in[0] == '#')
        // { // envoie à un seul joueur
        //     int client = 0;
        //     int read = sscanf(buffer_in, "%*[^0123456789]%d ", &client);
        //     for (int i = 0; i < current_room->nb_player; i++)
        //     {
        //         if (client == current_player->connection->index)
        //         {
        //             write(current_player->connection->sockfd, buffer_out, strlen(buffer_out));
        //             break;
        //         } //no client found ? : we dont care !!
        //     }
        // }
        // else
        // {
        //     write(current_player->connection->sockfd, buffer_out, strlen(buffer_out));
        // }

        //clear input buffer
        memset(buffer_in, '\0', BUFFERSIZE);
    }
    printf("Connection to client %i ended \n", current_player->connection->sockfd);
    close(current_player->connection->sockfd);
    del(current_player->connection);
    free(current_player->connection);
    pthread_exit(0);
}

int create_server_socket()
{
    parseConfig("server.ini");
    int sockfd = -1;
    struct sockaddr_in address;
    sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sockfd <= 0)
    {
        fprintf(stderr, "%s: error: cannot create socket\n");
        return -3;
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr(getServerIpAddress());
    address.sin_port = htons(getServerPort());
    int reuse = 1;
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (const char *)&reuse, sizeof(reuse));

    if (bind(sockfd, (struct sockaddr *)&address, sizeof(struct sockaddr_in)) < 0)
    {
        fprintf(stderr, "error: cannot bind socket to port %d\n", getServerPort());
        return -4;
    }

    return sockfd;
}
