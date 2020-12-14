#include <stdlib.h>
#include <sys/socket.h>
#include "response.h"
#include "../connection/manager.h"
#include "../../models/packetModel.h"
#include "../serialization/serialize.h"
#include "../buffer/write.h"

void reponse_PlayerIsConnected(Player *current_player)
{
    BufferWriteToClient(current_player, SerializeMessage(CONNECTED, "You are connected"));
}

void response_PlayerIsReady(Player *current_player)
{
    BufferWriteToClient(current_player, SerializeMessage(PLAYER_READY, "You are ready"));
}

void response_RoomIsReady(Room *current_room)
{
    BufferWriteToRoom(current_room, SerializeMessage(ROOM_READY, "Your room is ready"));
}

void response_EndOfGame(Room *current_room)
{
    BufferWriteToRoom(current_room, SerializeMessage(GAME_END, "The game end"));
}
