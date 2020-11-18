
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <pthread.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>

#include "srvcxnmanager.h"
#include "utils/ini.h"
#include "utils/configreader.h"

connection_t* connections[MAXSIMULTANEOUSCLIENTS];
Player_client* pl;
Room_of_palyer* room;

int test = 0;


int getMaxSimultaneousClients()
{
    ini_t *config = ini_load("serverConfig.ini");
    return atoi(ini_get(config, "network", "max_silmutaneous_connection"));
}

void init_sockets_array() {

    pl = (Player_client*)calloc(getMaxSimultaneousClients(),sizeof(Player_client));           // +++ Initialisation de player
    room = (Room_of_palyer*)calloc(getMaxSimultaneousClients()/2,sizeof(Room_of_palyer));     // +++ Initialisation de room

    for (int i = 0; i < getMaxSimultaneousClients(); i++) {
        connections[i] = NULL;
    }
}


void add(connection_t *connection) {                             // -+- void -> int
    for (int i = 0; i < getMaxSimultaneousClients(); i++) {
        if (pl[i].ocupation == 0) {
            printf("\nrang = %d\n", i);
            connections[i] = connection;                   // --- Suppression de connexions[]
            pl[i].cnx = connection;                        // +++ Ajout de connection dans player
            pl[i].ocupation = 1;                           // +++ Dire qu'il est occuper
            return;
        }
    }
    perror("Too much simultaneous connections");
    exit(-5);
}


void configurationRoom(connection_t *connection){                             // +++ Configuration du Room
    for (int i = 0; i < getMaxSimultaneousClients()/2; i++) {
        if (room[i].pl1 == 0){
            room[i].name = "1";
            room[i].pl1 = &pl[i];
            return;
        }

        if (room[i].pl2 == 0){
            room[i].pl2 = &pl[i+1];
            room[i].game_number = 1;
            return;
        }
    }
    perror("Error in room creation");
    //exit(-5);
}

// +++ Le salon de game
void game_start(int game_room){
    char buffer_in_pl1[BUFFERSIZE];
    char buffer_in_pl2[BUFFERSIZE];
    char buffer_out[BUFFERSIZE];
    int len_pl1;
    int len_pl2;
    int round = 0;
    
    printf("\n\n\n");

    printf("Toi tu est joueur #%d\n", room[game_room].pl1->cnx->index);
    sprintf(buffer_out, "Collaborer ou trahir joueur 2\n");
    write(room[game_room].pl1->cnx->sockfd, buffer_out, strlen(buffer_out));

    printf("Toi tu est joueur #%d\n", room[game_room].pl2->cnx->index);
    sprintf(buffer_out, "Collaborer ou trahir joueur 1\n");
    write(room[game_room].pl2->cnx->sockfd, buffer_out, strlen(buffer_out));

    printf("\n\n\n");

    while ((len_pl1 = read(room[game_room].pl1->cnx->sockfd, buffer_in_pl1, BUFFERSIZE)) > 0 || (len_pl2 = read(room[game_room].pl2->cnx->sockfd, buffer_in_pl2, BUFFERSIZE)) > 0 || round != 3){
        // +++ Si le joueur 1 collabore
        if (strncmp(buffer_in_pl1, "collaborer", strlen("collaborer")) == 0) {
            printf("Joueur %d collabore\n", room[game_room].pl1->cnx->index);
            room[game_room].pl2->point += 10;
            round += 1;
            printf("Point de joueur 2 : %d\n", room[game_room].pl2->point);
            sprintf(buffer_in_pl1, "");
        }


        // +++ Si le joueur 1 trahi
        if (strncmp(buffer_in_pl1, "trahir", strlen("trahir")) == 0) {
            printf("Joueur %d trahi \n", room[game_room].pl1->cnx->index);
            room[game_room].pl2->point += 10;
            round += 1;
            printf("Point de joueur 2 : %d", room[game_room].pl2->point);
            printf(buffer_in_pl1, "");

        }

    }

    printf("\nLa partie est terminee\n");
}



void del(connection_t *connection) {
    for (int i = 0; i < getMaxSimultaneousClients(); i++) {
        if (connections[i] == connection) {
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

/**
 * Thread allowing server to handle multiple client connections
 * @param ptr connection_t 
 * @return 
 */
void *threadProcess(void *ptr) {
    char buffer_in[BUFFERSIZE];
    char buffer_out[BUFFERSIZE];

    int len;
    connection_t *connection;

    if (!ptr) pthread_exit(0);
    connection = (connection_t *) ptr;
    printf("New incoming connection \n");

    add(connection);                                            // +++ Ajout de int potion
    configurationRoom(connection);                              // +++ Appel de la fonction de configuration de Room
    

    printf("Client 1 %d\n",pl[0].point);
    printf("Client 2 %d\n",pl[1].point);
    printf("\n");
    if (test == 1)
        printf("Client 2 %d\n",pl[1].cnx->index);
    test = 1;

    //Welcome the new client
    printf("Welcome #%i\n", connection->index);
    sprintf(buffer_out, "Welcome #%i\n", connection->index);
    write(connection->sockfd, buffer_out, strlen(buffer_out));


    // Ask if the player is ready
    sprintf(buffer_out, "Are you ready #%i\n", connection->index);
    write(connection->sockfd, buffer_out, strlen(buffer_out));

    while ((len = read(connection->sockfd, buffer_in, BUFFERSIZE)) > 0) {

        // +++ The player write ready if he is ready
        if (strncmp(buffer_in, "ready", strlen("ready")) == 0) {
            printf("Joueur %d est pret \n", connection->index);
            pl[connection->index-1].ready = 1;
        }

        // +++ if the 2 player of the room are ready the game will start
        for (int i = getMaxSimultaneousClients()/2-1; i>=0; i--){
            if (room[i].game_number == 1){
                if (room[i].pl1[i].ready == 1 && room[i].pl2[i].ready == 1 && room[i].pl1[i].ocupation == 1 && room[i].pl2[i].ocupation == 1){
                    printf("The players are ready !\n");
                    printf("index %d\n", room[0].pl1[0].cnx->index);
                    printf("index %d\n", room[0].pl1[1].cnx->index);
                    room[i].game_number = 2;
                    game_start(i);                
                }
            }
        }

        if (strncmp(buffer_in, "bye", 3) == 0) {
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

        if (buffer_in[0] == '@') {
            for (int i = 0; i < getMaxSimultaneousClients(); i++) {
                if (connections[i] != NULL) {
                    write(connections[i]->sockfd, buffer_out, strlen(buffer_out));
                }
            }
        } else if (buffer_in[0] == '#') {
            int client = 0;
            int read = sscanf(buffer_in, "%*[^0123456789]%d ", &client);
            for (int i = 0; i < getMaxSimultaneousClients(); i++) {
                if (client == connections[i]->index) {
                    write(connections[i]->sockfd, buffer_out, strlen(buffer_out));
                    break;
                } //no client found ? : we dont care !!
            }
        } else {
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

int create_server_socket() {
	ini_t *config = ini_load("serverConfig.ini");
    int sockfd = -1;
    struct sockaddr_in address;

    Config *configuration;
    read_configuration(configuration, "games.cfg");
   
    /* create socket */
    sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sockfd <= 0) {
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
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (const char*) &reuse, sizeof (reuse));

    /* bind */
    if (bind(sockfd, (struct sockaddr *) &address, sizeof (struct sockaddr_in)) < 0) {
        fprintf(stderr, "error: cannot bind socket to port %d\n", atoi(ini_get(config, "network", "server_port")));
        return -4;
    }

    return sockfd;
}
