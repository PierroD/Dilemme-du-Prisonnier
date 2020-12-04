#ifndef ROOM_H
#define ROOM_H

#include <stdlib.h>
#include <stdbool.h>
#include <sys/socket.h>
#include "../srvcxnmanager.h"
#include "player.h"


typedef struct {
    int id_room;
    int nb_player;
    Player *players;
} Room;

void init_rooms();
Room *addPlayerToRoom(Room *current_room, int player_index, Player *add_player);
Room *configureRoom(Player *player);
void setPlayerToReady(Room *current_room, Player *current_player);
int isRoomReady(Room *current_room);
void printRoom(Room room);

#endif /* ROOM_H */
