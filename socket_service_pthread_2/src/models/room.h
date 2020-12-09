#ifndef ROOM_H
#define ROOM_H

#include <stdbool.h>
#include "player.h"

typedef struct
{
    int id_room;
    int nb_player;
    Player *players;
} Room;

void init_rooms();
Room *addPlayerToRoom(Room *current_room, int player_index, Player *add_player);
Room *configureRoom(Player *player);
void setPlayerToReady(Room *current_room, Player *current_player);
bool isRoomReady(Room *current_room);

#endif /* ROOM_H */
