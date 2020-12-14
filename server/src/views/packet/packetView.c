#include "packetView.h"
#include "../offset/offsetView.h"
#include "../../utils/config/parser.h"

void view_writePacketSentInfo(Packet *packet, int player_id)
{
    if (getShowPacket())
    {
        printf("\033[1;34m SERVER \033[0mpacket sent type \033[0;32m%s\033[0m to \033[1;32m#%d\033[0m.\n", action_str[packet->code], player_id);
        writeOffset(packet);
    }
}

void view_writePacketReceivedInfo(Packet *packet, int player_id)
{
    if (getShowPacket())
    {
        printf("\033[1;34m SERVER \033[0mpacket received type \033[0;32m%s\033[0m from \033[1;32m#%d\033[0m.\n", action_str[packet->code], player_id);
        writeOffset(packet);
    }

}