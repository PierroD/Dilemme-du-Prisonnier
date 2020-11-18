
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <pthread.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>

#include "srvcxnmanager.h"
#include "utils/ini.h"

connection_t *connections[MAXSIMULTANEOUSCLIENTS];
Room *rooms;

int test = 0;

int getMaxSimultaneousClients()
{
    ini_t *config = ini_load("serverConfig.ini");
    return atoi(ini_get(config, "network", "max_silmutaneous_connection"));
}

void init_sockets_array()
{
    rooms = (Room *)calloc(getMaxSimultaneousClients() / 2, sizeof(Room));
    rooms->players = (Player *)calloc(2, sizeof(Player));
    for (int i = 0; i < getMaxSimultaneousClients(); i++)
    {
        connections[i] = NULL;
    }
}

Player create_player(connection_t *connection)
{
    Player player;
    player.connection = connection;
    return player;
}

Room addPlayerToRoom(Room current_room, int room_index, int player_index, Player add_player)
{
    current_room.nb_player++;
    current_room.players[player_index] = add_player;
    current_room.players[player_index].in_room = true;
    rooms[room_index] = current_room;
    return current_room;
}

Room configureRoom(Player player)
{
    for (int i = 0; i < getMaxSimultaneousClients() / 2; i++)
    {

        if (rooms[i].id_room == 0)
        {
            rooms[i].id_room = i + 1;
            return addPlayerToRoom(rooms[i], i, 0, player);
        }
        else
            for (int j = 1; j < 2; j++)
                if (rooms[i].players[j].in_room == false)
                    return addPlayerToRoom(rooms[i], i, j, player);
    }
}

void printRoom(Room room)
{
    printf("Index de la room : %d\n", room.id_room);
    printf("Nombre de joueurs : %d\n", room.nb_player);
    for (int i = 0; i < room.nb_player; i++)
        printf("index du joueur : %d\n", room.players[i].connection->index);
}
// +++ Le salon de game
void game_start(int game_room)
{
    char buffer_in_pl1[BUFFERSIZE];
    char buffer_in_pl2[BUFFERSIZE];
    char buffer_out[BUFFERSIZE];
    int len_pl1;
    int len_pl2;
    int round = 0;

    // printf("\n\n\n");

    // printf("Toi tu est joueur #%d\n", room[game_room].pl1->cnx->index);
    // sprintf(buffer_out, "Collaborer ou trahir joueur 2\n");
    // write(room[game_room].pl1->cnx->sockfd, buffer_out, strlen(buffer_out));

    // printf("Toi tu est joueur #%d\n", room[game_room].pl2->cnx->index);
    // sprintf(buffer_out, "Collaborer ou trahir joueur 1\n");
    // write(room[game_room].pl2->cnx->sockfd, buffer_out, strlen(buffer_out));

    // printf("\n\n\n");

    // while ((len_pl1 = read(room[game_room].pl1->cnx->sockfd, buffer_in_pl1, BUFFERSIZE)) > 0 || (len_pl2 = read(room[game_room].pl2->cnx->sockfd, buffer_in_pl2, BUFFERSIZE)) > 0 || round != 3)
    // {
    //     // +++ Si le joueur 1 collabore
    //     if (strncmp(buffer_in_pl1, "collaborer", strlen("collaborer")) == 0)
    //     {
    //         printf("Joueur %d collabore\n", room[game_room].pl1->cnx->index);
    //         room[game_room].pl2->point += 10;
    //         round += 1;
    //         printf("Point de joueur 2 : %d\n", room[game_room].pl2->point);
    //         sprintf(buffer_in_pl1, "");
    //     }

    //     // +++ Si le joueur 1 trahi
    //     if (strncmp(buffer_in_pl1, "trahir", strlen("trahir")) == 0)
    //     {
    //         printf("Joueur %d trahi \n", room[game_room].pl1->cnx->index);
    //         room[game_room].pl2->point += 10;
    //         round += 1;
    //         printf("Point de joueur 2 : %d", room[game_room].pl2->point);
    //         printf(buffer_in_pl1, "");
    //     }
    // }

    // printf("\nLa partie est terminee\n");
}

void del(connection_t *connection)
{
    for (int i = 0; i < getMaxSimultaneousClients(); i++)
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
/*
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_lock(&lock);
pthread_mutex_unlock(&lock);
 */

int isRoomReady(Room current_room)
{
    /*#if DEBUG
        printf("DEBUG-----------------------------------------------------------\n");
        printf("p1 : %d \n", current_room.players[0].ready);
        printf("p2 : %d \n", current_room.players[1].ready);
        printf("----------------------------------------------------------------\n");
    #endif*/

    for (int i = 0; i < 2; i++)
        if (current_room.players[i].ready != true)
            return false;

    return true;
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

    Player current_player = create_player(connection);
    Room current_room = configureRoom(current_player);
    /*#if DEBUG
        printf("DEBUG-----------------------------------------------------------\n");
        printRoom(rooms[0]);
        printf("----------------------------------------------------------------\n");
    #endif*/
    //Welcome the new client
    printf("Welcome #%i\n", current_player.connection->index);
    sprintf(buffer_out, "Welcome #%i\n", current_player.connection->index);
    write(current_player.connection->sockfd, buffer_out, strlen(buffer_out));

    // Ask if the player is ready
    sprintf(buffer_out, "Are you ready #%i ? \n", current_player.connection->index);
    write(current_player.connection->sockfd, buffer_out, strlen(buffer_out));

    while ((len = read(current_player.connection->sockfd, buffer_in, BUFFERSIZE)) > 0)
    {
        // change player.ready status
        if (strncmp(buffer_in, "ready", strlen("ready")) == 0)
        {
            printf("Joueur %d est pret \n", current_player.connection->index);
            current_room.players[current_player.connection->index - 1].ready = true;
        }
        if (isRoomReady(current_room))
            printf("On lance la partie \n");
        // +++ if both players in the current room are ready the game will start

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
        strcpy(buffer_out, "\nServer Echo : ");
        strncat(buffer_out, buffer_in, len);

        if (buffer_in[0] == '@')
        { // envoie à tous les clients
            for (int i = 0; i < current_room.nb_player; i++)
            {
                if (current_room.players[i].connection != NULL)
                {
                    write(current_room.players[i].connection->sockfd, buffer_out, strlen(buffer_out));
                }
            }
        }
        else if (buffer_in[0] == '#')
        { // envoie à un seul client
            int client = 0;
            int read = sscanf(buffer_in, "%*[^0123456789]%d ", &client);
            for (int i = 0; i < current_room.nb_player; i++)
            {
                if (client == current_room.players[i].connection->index)
                {
                    write(current_room.players[i].connection->sockfd, buffer_out, strlen(buffer_out));
                    break;
                } //no client found ? : we dont care !!
            }
        }
        else
        {
            write(connection->sockfd, buffer_out, strlen(buffer_out));
        }

        //clear input buffer
        memset(buffer_in, '\0', BUFFERSIZE);
    }
    printf("Connection to client %i ended \n", connection->index);
    close(connection->sockfd);
    del(connection);
    free(connection);
    pthread_exit(0);
}

int create_server_socket()
{
    ini_t *config = ini_load("serverConfig.ini");
    int sockfd = -1;
    struct sockaddr_in address;

    /* create socket */
    sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sockfd <= 0)
    {
        fprintf(stderr, "%s: error: cannot create socket\n");
        return -3;
    }

    /* bind socket to port */
    address.sin_family = AF_INET;
    //bind to all ip :
    //address.sin_addr.s_addr = INADDR_ANY;
    //ou 0.0.0.0
    //Sinon  127.0.0.1
    address.sin_addr.s_addr = inet_addr(ini_get(config, "network", "server_ip_address"));
    address.sin_port = htons(atoi(ini_get(config, "network", "server_port")));

    /* prevent the 60 secs timeout */
    int reuse = 1;
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (const char *)&reuse, sizeof(reuse));

    /* bind */
    if (bind(sockfd, (struct sockaddr *)&address, sizeof(struct sockaddr_in)) < 0)
    {
        fprintf(stderr, "error: cannot bind socket to port %d\n", atoi(ini_get(config, "network", "server_port")));
        return -4;
    }

    return sockfd;
}
