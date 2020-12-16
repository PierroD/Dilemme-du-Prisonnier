/**
 * \file        manager.c
 * \brief       Gestion threads et sockets
 * */


#include <arpa/inet.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../config/parser.h"
#include "../table/fort.h"
#include "../buffer/read.h"
#include "../packet/processor.h"
#include "../../controllers/player/playerController.h"
#include "../../controllers/room/roomController.h"
#include "../../views/room/roomView.h"
#include "../../views/packet/packetView.h"
#include "manager.h"


Config configfile;

/**
 * Thread allowing server to handle multiple client connections
 * @param ptr connection_t 
 *
 * @return un pointeur
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

    Player *current_player = PlayerCreate(connection);
    view_writePlayerInfo(current_player);
    Room *current_room = RoomAssignToPlayer(current_player);
    view_writeRoomInfo(current_room);
    reponse_PlayerIsConnected(current_player);

    while ((len = read(current_player->connection->sockfd, buffer_in, BUFFERSIZE)) > 0)
    {
        Packet *receive_packet = BufferRead(current_room, current_player, buffer_in, len);
        //clear input buffer
        view_writePacketReceivedInfo(receive_packet, current_player->id);
        memset(buffer_in, '\0', BUFFERSIZE);
        PacketProcessor(receive_packet, current_room, current_player);
    }
    printf("Connection to client %i ended \n", current_player->connection->sockfd);
    // del(current_player->connection);
    pthread_exit(0);
}


/**
 * Creation du socket du serveur
 *
 * @return le socket du serveur
 * 
 * */

int create_server_socket()
{
    ParseConfig("server.ini");
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

    // print Server info
    char port[5];
    sprintf(port, "%d", getServerPort());
    ft_table_t *table = ft_create_table();
    // Set "header" type for the first row
    ft_set_cell_prop(table, 0, FT_ANY_COLUMN, FT_CPROP_ROW_TYPE, FT_ROW_HEADER);
    ft_write_ln(table, "Server", "IP Address", "Port");
    ft_write_ln(table, "", getServerIpAddress(), port);
    printf("%s\n", ft_to_string(table));
    ft_destroy_table(table);

    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (const char *)&reuse, sizeof(reuse));

    if (bind(sockfd, (struct sockaddr *)&address, sizeof(struct sockaddr_in)) < 0)
    {
        fprintf(stderr, "error: cannot bind socket to port %d\n", getServerPort());
        return -4;
    }

    return sockfd;
}
