#ifndef BUFFERREADER_H
#define BUFFERREADER_H
#define BUFFERSIZE 2048

// TODO :en avoir le minimum
#include <stdbool.h>
#include "../models/player.h"
#include "../models/room.h"
#include "../models/response.h"
#include "../srvcxnmanager.h"


void read_buffer(Room *current_room,Player *current_player,char *buffer_in, int buffer_size);
void write_buffer_to_room(Room *current_room, int code);
void write_buffer_to_client(Player *current_player, int code);
void write_buffer(int playerSocket, int code);
#endif /* BUFFERREADER_H */
