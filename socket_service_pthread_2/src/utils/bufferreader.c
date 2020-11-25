#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include "bufferreader.h"


void read_buffer(Room *current_room, Player *current_player,char buffer_in[], int buffer_size){
    if(strncmp(buffer_in,"ready",5)==0) 
    {
            setPlayerToReady(current_room, current_player);
            PlayerIsReady(current_player);
            if(isRoomReady(current_room))
                RoomIsReady(current_room);
    }
}

void write_buffer_to_room(Room *current_room, ACTION action)
{
    for(int i=0; i<current_room->nb_player; i++)
           write_buffer_to_client((current_room->players + i * sizeof(Player)), action);
}

void write_buffer_to_client(Player *current_player, ACTION action)
{
    write_buffer(current_player->connection->sockfd, action);
}

void write_buffer(int playerSocket, ACTION action)
{
    write(playerSocket, action, strlen(action));
}

