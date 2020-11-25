#ifndef RESPONSE_H
#define RESPONSE_H

#include <stdlib.h>
#include <sys/socket.h>
#include "../srvcxnmanager.h"
#include "../utils/bufferreader.h"
#include "player.h"

enum action{
    CONNECTED,
    PLAYER_READY,
    ROOM_READY
};


typedef struct {
    int id_envoyeur;
    int id_receveur;
    enum action code;
    int size_data;
    char data[];
}Packet; 


#endif /* RESPONSE_H */