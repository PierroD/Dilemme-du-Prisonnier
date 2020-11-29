#include "response.h"

void PlayerIsConnected(Player *current_player)
{
    write_buffer_to_client(current_player, serializeMessage(CONNECTED, "You are connected"));
}

void PlayerIsReady(Player *current_player)
{
        write_buffer_to_client(current_player, serializeMessage(PLAYER_READY, "You are ready"));
}

void RoomIsReady(Room *current_room)
{
    write_buffer_to_room(current_room, serializeMessage(ROOM_READY, "Your room is ready"));
}