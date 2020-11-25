#ifndef BUFFERREADER_H
#define BUFFERREADER_H
#define BUFFERSIZE 2048

#include "../models/player.h"
#include "../models/room.h"
#include "../models/response.h"
#include "../srvcxnmanager.h"

#define true 1
#define false 0

void read_buffer(Room *current_room,Player *current_player,char *buffer_in, int buffer_size);
void write_buffer_to_room(Room *current_room, ACTION action);
void write_buffer_to_client(Player *current_player, ACTION action);
void write_buffer(int playerSocket, ACTION action);
#endif /* BUFFERREADER_H */
