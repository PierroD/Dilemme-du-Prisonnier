#ifndef BUFFERREADER_H
#define BUFFERREADER_H
#define BUFFERSIZE 2048

// TODO :en avoir le minimum
#include <stdbool.h>
#include "../includes/packet.h"
#include "../models/response.h"
#include "../models/player.h"
#include "../models/room.h"
#include "../srvcxnmanager.h"


void read_buffer(Room *current_room,Player *current_player,char *buffer_in, int buffer_size);
void write_buffer_to_room(Room *current_room, Packet *packet);
void write_buffer_to_client(Player *current_player, Packet *packet);
void write_buffer(int playerSocket, Packet *packet);
#endif /* BUFFERREADER_H */
