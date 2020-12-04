#include "packetprocessor.h"

void process_packet(Packet *packet, Room *current_room, Player *current_player)
{
    switch (packet->code)
        {
        case PLAYER_READY:
            setPlayerToReady(current_room, current_player);
            response_PlayerIsReady(current_player);
            if (isRoomReady(current_room))
            {
                response_RoomIsReady(current_room);
                start_game(current_room);
            }
            break;
        }
}