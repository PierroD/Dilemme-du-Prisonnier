#ifndef RESPONSE_H
#define RESPONSE_H

#include <stdlib.h>
#include <sys/socket.h>
#include "../srvcxnmanager.h"
#include "player.h"
#include "../utils/bufferreader.h"

typedef enum ACTION{
    CONNECTED,
    PLAYER_READY,
    ROOM_READY
};

// typedef struct {
//     int id_envoyer;
//     int id_destinataire;
//     enum ACTION action;
//     int size_data;
//     char data[32];
// } Packet;

#endif /* RESPONSE_H */