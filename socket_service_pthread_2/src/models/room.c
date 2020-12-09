#include <stdlib.h>
#include <sys/socket.h>
#include "room.h"
#include "../srvcxnmanager.h"

Room *rooms = NULL;

void init_rooms()
{
    rooms = (Room *)calloc(getMaxSimultaneousConnection() / getMaxPlayerPerRoom(), sizeof(Room));
    for (int i = 0; i < getMaxSimultaneousConnection() / getMaxPlayerPerRoom(); i++)
        rooms[i].players = (Player *)calloc(getMaxPlayerPerRoom(), sizeof(Player));
}

Room *addPlayerToRoom(Room *current_room, int player_index, Player *add_player)
{
    current_room->nb_player++;
    add_player->in_room = true;
    memcpy((current_room->players + (player_index * sizeof(Player))), add_player, sizeof(Player));
    return current_room;
}

Room *configureRoom(Player *player)
{
    if (rooms == NULL)
        init_rooms();
    for (int i = 0; i < getMaxSimultaneousConnection() / getMaxPlayerPerRoom(); i++)
    {
        if (rooms[i].id_room == 0)
        {
            rooms[i].id_room = i + 1;
            return addPlayerToRoom(&rooms[i], 0, player);
        }
        else
            for (int j = 1; j < getMaxPlayerPerRoom(); j++)
                if (rooms[i].players[j].in_room == false)
                    return addPlayerToRoom(&rooms[i], j, player);
    }
}

void setPlayerToReady(Room *current_room, Player *current_player)
{
    for (int i = 0; i < current_room->nb_player; i++)
    {
        Player player = *(current_room->players + i * sizeof(Player));
        if (player.id == current_player->id)
        {
            current_room->players[i].ready = true;
            current_player->ready = true;
            break;
        }
    }
}

bool isRoomReady(Room *current_room)
{
    for (int i = 0; i < getMaxPlayerPerRoom(); i++)
    {
        if (current_room->players[i].ready == false)
            return false;
    }
    return true;
}

