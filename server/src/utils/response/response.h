#ifndef RESPONSE_H
#define RESPONSE_H
#include "../../models/roomModel.h"
#include "../../models/playerModel.h"


void reponse_PlayerIsConnected(Player *current_player);
void response_PlayerIsReady(Player *current_player);
void response_RoomIsReady(Room *current_room);
void response_EndOfGame(Room *current_room);

#endif /* RESPONSE_H */