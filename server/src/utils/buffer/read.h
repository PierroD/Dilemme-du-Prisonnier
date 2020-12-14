#ifndef READ_H
#define READ_H

// TODO :en avoir le minimum
#include "../../models/packetModel.h"
#include "../../models/playerModel.h"
#include "../../models/roomModel.h"

Packet *BufferRead(Room *current_room, Player *current_player, char *buffer_in, int buffer_size);
#endif /* READ_H */
