#ifndef WRITE_H
#define WRITE_H

#include "../../models/packetModel.h"
#include "../../models/playerModel.h"
#include "../../models/roomModel.h"

void BufferWriteToRoom(Room *current_room, Packet *packet);
void BufferWriteToClient(Player *current_player, Packet *packet);
void BufferWrite(int playerSocket, Packet *packet);

#endif /* WRITE_H */
