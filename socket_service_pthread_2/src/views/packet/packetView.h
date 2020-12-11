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
};

void view_writePacketInfo(Packet *packet, int player_id, bool show_offset);
#endif /* PACKETVIEW_H */