#include "room.h"

Room *rooms = NULL;
void init_rooms()
{
    rooms = (Room *)calloc(getMaxSimultaneousConnection() / 2, sizeof(Room));
    rooms->players = (Player *)calloc(2, sizeof(Player));
}

Room *addPlayerToRoom(Room *current_room, int player_index, Player *add_player)
{
    current_room->nb_player++;
    memcpy((current_room->players + (player_index * sizeof(Player))), add_player, sizeof(Player));
    current_room->players[player_index].in_room = true;
    return current_room;
}

Room *configureRoom(Player *player)
{
    if (rooms == NULL)
        init_rooms();
    for (int i = 0; i < getMaxSimultaneousConnection() / 2; i++)
    {
        if (rooms[i].id_room == 0)
        {
            rooms[i].id_room = i + 1;
            return addPlayerToRoom(&rooms[i], i, player);
        }
        else
            for (int j = 1; j < 2; j++)
                if (rooms[i].players[j].in_room == false)
                    return addPlayerToRoom(&rooms[i], j, player);
    }
}

void setPlayerToReady(Room *current_room, Player *current_player)
{
    for (int i = 0; i < current_room->nb_player; i++)
    {
        Player tested_player = *(current_room->players + i * sizeof(Player));
        if (tested_player.id == current_player->id)
        {
            current_room->players[i].ready = true;
            current_player->ready = true;
            break;
        }
    }
}

Player *getPlayerbyId(Room *current_room, int id)
{
    for (int i = 0; i < current_room->nb_player + 1; i++)
    {
        Player p2 = *(current_room->players + i * sizeof(Player));
        if (p2.id == id)
            return &current_room->players[i];
    }
    Player *p = (Player *)calloc(1, sizeof(Player));
    return p;
}

int isRoomReady(Room *current_room)
{
    /*#if DEBUG
        printf("DEBUG-----------------------------------------------------------\n");
        printf("p1 : %d \n", current_room->players[0].ready);
        printf("p2 : %d \n", current_room->players[1].ready);
        printf("----------------------------------------------------------------\n");
    #endif*/

    for (int i = 1; i < 3; i++)
    {
        Player *p = getPlayerbyId(current_room, i);
        if (p->ready != true)
            return false;
    }
    return true;
}

void printRoom(Room room)
{
    printf("Index de la room : %d\n", room.id_room);
    printf("Nombre de joueurs : %d\n", room.nb_player);
    for (int i = 0; i < room.nb_player; i++)
        printf("index du joueur : %d\n", room.players[i].connection->index);
}