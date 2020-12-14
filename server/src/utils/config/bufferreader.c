#include "bufferreader.h"

Packet *read_buffer(Room *current_room, Player *current_player, char *buffer_in, int buffer_size)
{
   return deserialize(buffer_in); 
}

void write_buffer_to_room(Room *current_room, Packet *packet)
{
    for (int i = 0; i < current_room->nb_player; i++)
        write_buffer_to_client((current_room->players+ i * sizeof(Player)), packet); //  
}

void write_buffer_to_client(Player *current_player, Packet *packet)
{
    write_buffer(current_player->connection->sockfd, packet);
}

void write_buffer(int playerSocket, Packet *packet)
{
    write(playerSocket, packet, sizeof(Packet));
}