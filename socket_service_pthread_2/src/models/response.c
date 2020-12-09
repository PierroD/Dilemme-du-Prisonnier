#include <stdlib.h>
#include <sys/socket.h>
#include "response.h"
#include "../srvcxnmanager.h"
#include "../includes/packet.h"
#include "../utils/serialize.h"
#include "../utils/bufferreader.h"

void reponse_PlayerIsConnected(Player *current_player)
{
    write_buffer_to_client(current_player, serializeMessage(CONNECTED, "You are connected"));
}

void response_PlayerIsReady(Player *current_player)
{
    write_buffer_to_client(current_player, serializeMessage(PLAYER_READY, "You are ready"));
}

void response_RoomIsReady(Room *current_room)
{
    write_buffer_to_room(current_room, serializeMessage(ROOM_READY, "Your room is ready"));
}

void response_EndOfGame(Room *current_room)
{
    write_buffer_to_room(current_room, serializeMessage(GAME_END, "The game end"));
}
