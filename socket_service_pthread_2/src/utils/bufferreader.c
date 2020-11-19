#include "bufferreader.h"


void read_buffer(Room *current_room, Player *current_player,char buffer_in[], int buffer_size){
    printf("buffer content : %s \n", buffer_in);
    if(strncmp(buffer_in,"ready",5)==0) 
    {
            setPlayerToReady(current_room, current_player);
            write_buffer(current_player, "Player is ready\n");
            if(isRoomReady(current_room))
                write_buffer(current_player, "The room is ready\n");
    }

}

void write_buffer(Player *current_player, char message[])
{
    write(current_player->connection->sockfd, message, strlen(message));
}