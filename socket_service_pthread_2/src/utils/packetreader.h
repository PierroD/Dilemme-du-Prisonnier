#ifndef PACKETREADER_h
#define PACKETREADER_h

#include "../models/room.h"
#include "../models/player.h"
#include "../includes/packet.h"
#include "../models/game.h"

void read_packet(Packet *packet, Room *current_room, Player *current_player);

#endif /* PACKETREADER_h */