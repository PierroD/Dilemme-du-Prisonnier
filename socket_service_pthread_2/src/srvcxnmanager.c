
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

int getMaxSimultaneousClients()
{
    ini_t *config = ini_load("serverConfig.ini");
    return atoi(ini_get(config, "network", "max_silmutaneous_connection"));
}

void init_sockets_array() {
    for (int i = 0; i < getMaxSimultaneousClients(); i++) {
        connections[i] = NULL;
    }
}

void add(connection_t *connection) {
    for (int i = 0; i < getMaxSimultaneousClients(); i++) {
        if (connections[i] == NULL) {
            connections[i] = connection;
            return;
        }
    }
    perror("Too much simultaneous connections");
    exit(-5);
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

    add(connection);

    //Welcome the new client
    printf("Welcome #%i\n", connection->index);
    sprintf(buffer_out, "Welcome #%i\n", connection->index);
    write(connection->sockfd, buffer_out, strlen(buffer_out));

    while ((len = read(connection->sockfd, buffer_in, BUFFERSIZE)) > 0) {

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
