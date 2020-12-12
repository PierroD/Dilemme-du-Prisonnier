#include "write.h"
#include "../../views/packet/packetView.h"
void BufferWriteToRoom(Room *current_room, Packet *packet)
{
    for (int i = 0; i < current_room->nb_player; i++)
        BufferWriteToClient((current_room->players + i * sizeof(Player)), packet); //
}

void BufferWriteToClient(Player *current_player, Packet *packet)
{
    view_writePacketSentInfo(packet, current_player->id);
    BufferWrite(current_player->connection->sockfd, packet);
}

void BufferWrite(int playerSocket, Packet *packet)
{
    write(playerSocket, packet, sizeof(Packet));
}