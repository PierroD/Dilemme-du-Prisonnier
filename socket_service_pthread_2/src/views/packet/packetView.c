#include "packetView.h"
#include "../offset/offsetView.h"

void view_writePacketInfo(Packet *packet, int player_id, bool show_offsets)
{
    printf("\033[1;34m SERVER \033[0mpacket type \033[0;32m%s\033[0m to \033[1;32m#%d\033[0m.\n", action_str[packet->code], player_id);
    if (show_offsets)
        writeOffset(packet);
}