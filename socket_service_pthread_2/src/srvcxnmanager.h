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
    connection_t* cnx;
} Player_client;

typedef struct {
    char* name;
    int game_number;
    Player_client* pl1;
    Player_client* pl2;
} Room_of_palyer;


void init_sockets_array();
void add(connection_t *connection);
void del(connection_t *connection);
void *threadProcess(void *ptr);
int create_server_socket() ;

#endif /* SRVCXNMANAGER_H */

