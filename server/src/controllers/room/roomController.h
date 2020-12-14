#ifndef ROOMCONTROLLER_h
#define ROOMCONTROLLER_h

#include <stdbool.h>
#include "../../models/playerModel.h"
#include "../../models/roomModel.h"

void RoomsInitialize();
Room *RoomAddPlayer(Room *current_room, int player_index, Player *add_player);
Room *RoomAssignToPlayer(Player *player);
void RoomSetPlayerToReady(Room *current_room, Player *current_player);
bool isRoomReady(Room *current_room);

#endif /* ROOMCONTROLLER_h */
