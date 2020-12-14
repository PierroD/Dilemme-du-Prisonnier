#ifndef PACKETPROCESSOR_h
#define PACKETPROCESSOR_h

#include "../models/room.h"
#include "../models/player.h"
#include "../models/response.h"
#include "../includes/packet.h"
#include "../models/game.h"

void process_packet(Packet *packet, Room *current_room, Player *current_player);

#endif /* PACKETPROCESSOR_h */