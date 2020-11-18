/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   srvcxnmanager.h
 * Author: aurelio
 *
 */

#ifndef SRVCXNMANAGER_H
#define SRVCXNMANAGER_H

#define BUFFERSIZE 2048
#define MAXSIMULTANEOUSCLIENTS 100

#define true 1
#define false 0

typedef struct {
    int sockfd;
    struct sockaddr address;
    int addr_len;
    int index;
} connection_t;

typedef struct {
    int ocupation;
    int point;
    int ready;
    connection_t* connection;
} Player;

typedef struct {
    int id_room;
    int nb_player;
    Player *players;
} Room;


void init_sockets_array();
Player create_player(connection_t *connection);
void del(connection_t *connection);
void *threadProcess(void *ptr);
int create_server_socket() ;

#endif /* SRVCXNMANAGER_H */

