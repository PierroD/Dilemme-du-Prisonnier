#ifndef MANAGER_H
#define MANAGER_H

#define BUFFERSIZE 2048
#define MAXSIMULTANEOUSCLIENTS 100




#include <sys/socket.h>
#include <unistd.h>


typedef struct {
    int sockfd;
    struct sockaddr address;
    int addr_len;
    int index;
} connection_t;


// void init_sockets_array();
// void del(connection_t *connection);
void *threadProcess(void *ptr);
int create_server_socket() ;

#endif /* MANAGER_H */

