#include "packetreader.h"

void read_packet(Packet *packet, Room *current_room, Player *current_player)
{
    switch (packet->code)
        {
        case PLAYER_READY:
            setPlayerToReady(current_room, current_player);
            PlayerIsReady(current_player);
            if (isRoomReady(current_room))
            {
                RoomIsReady(current_room);
                start_game(current_room);
            }
            break;
        }
}