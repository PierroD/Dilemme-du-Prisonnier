#ifndef BUFFERREADER_H
#define BUFFERREADER_H
#define BUFFERSIZE 2048

#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include "../models/player.h"
#include "../models/room.h"
#include "../srvcxnmanager.h"
#include "switchs.h"

#define true 1
#define false 0

void read_buffer(Room *current_room,Player *current_player,char *buffer_in, int buffer_size);
void write_buffer();

#endif /* BUFFERREADER_H */
