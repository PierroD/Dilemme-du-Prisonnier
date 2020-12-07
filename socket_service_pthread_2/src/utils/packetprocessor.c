#include "packetprocessor.h"

void process_packet(Packet *packet, Room *current_room, Player *current_player)
{
    switch (packet->code)
    {
    case PLAYER_READY:
    {
        setPlayerToReady(current_room, current_player);
        if (isRoomReady(current_room))
        {
            response_RoomIsReady(current_room);
            sleep(1);
            start_game(current_room);
        }
        else
            response_PlayerIsReady(current_player);

        break;
    }
    case RESPONSE:
    {
        Answer *answer = (Answer *)packet->data;
        answer->player_id = current_player->id;
        addChoiceToGame(current_room, answer);
        break;
    }
    }
}