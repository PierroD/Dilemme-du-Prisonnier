#ifndef PACKETVIEW_H
#define PACKETVIEW_H

#include <stdbool.h>
#include "../../models/packetModel.h"

static const char *action_str[] = {
    "CONNECTED",
    "PLAYER_READY",
    "ROOM_READY",
    "ASK_CHOICE",
    "RESPONSE",
    "GAME_END",
    "DISCONNECT",
};

void view_writePacketSentInfo(Packet *packet, int player_id);
void view_writePacketReceivedInfo(Packet *packet, int player_id);

#endif /* PACKETVIEW_H */