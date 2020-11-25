#include "response.h"



void PlayerIsConnected(Player *current_player)
{
    write_buffer_to_client(current_player, CONNECTED);
}

void PlayerIsReady(Player *current_player)
{
        write_buffer_to_client(current_player, PLAYER_READY);
}

void RoomIsReady(Room *current_room)
{
    write_buffer_to_room(current_room, ROOM_READY);
}