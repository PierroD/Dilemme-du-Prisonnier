#ifndef RESPONSE_H
#define RESPONSE_H
#include <stdlib.h>
#include <sys/socket.h>
#include "../srvcxnmanager.h"
#include "../includes/packet.h"
#include "../utils/serialize.h"
#include "../utils/bufferreader.h"
#include "room.h"
#include "player.h"


void reponse_PlayerIsConnected(Player *current_player);
void response_PlayerIsReady(Player *current_player);
void response_RoomIsReady(Room *current_room);


#endif /* RESPONSE_H */