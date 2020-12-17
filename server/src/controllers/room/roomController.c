/**
 * \file        roomController.c
 * \brief       Controleur de salle d'attente
 * */


#include <stdlib.h>
#include <sys/socket.h>
#include "roomController.h"
#include "../../utils/connection/manager.h"

Room *rooms = NULL;

/**
 * Initialisation de la salle d'attente
 * 
 * */

void RoomsInitialize()
{
    rooms = (Room *)calloc(getMaxSimultaneousConnection() / getMaxPlayerPerRoom(), sizeof(Room));
    for (int i = 0; i < getMaxSimultaneousConnection() / getMaxPlayerPerRoom(); i++)
        rooms[i].players = (Player *)calloc(getMaxPlayerPerRoom(), sizeof(Player));
}

/**
 * Ajout des joueurs dans la salle d'attente
 *
 * @param current_room salle d'attente
 * 
 * @param player_index index du joueur
 * 
 * @param add_player joueur ajouter
 * 
 * @return salle d'attente
 * 
 * */

Room *RoomAddPlayer(Room *current_room, int player_index, Player *add_player)
{
    current_room->nb_player++;
    add_player->in_room = true;
    memcpy((current_room->players + (player_index * sizeof(Player))), add_player, sizeof(Player));
    return current_room;
}

/**
 * Assigner un joueur a une salle d'attente
 *
 * @param player joueur
 * 
 * @return salle d'attente
 * 
 * */

Room *RoomAssignToPlayer(Player *player)
{
    if (rooms == NULL)
        RoomsInitialize();
    for (int i = 0; i < getMaxSimultaneousConnection() / getMaxPlayerPerRoom(); i++)
    {
        if (rooms[i].id_room == 0)
        {
            rooms[i].id_room = i + 1;
            return RoomAddPlayer(&rooms[i], 0, player);
        }
        else
            for (int j = 1; j <= getMaxPlayerPerRoom() - 1; j++) // i * getMaxPlayerPerRoom() + 1 // + i * getMaxPlayerPerRoom() - 1
                if (rooms[i].players[j].in_room == false && player->id <= (j + 1 + i * getMaxPlayerPerRoom()))
                    return RoomAddPlayer(&rooms[i], j, player);
    }
}

/**
 * Change l'etat du joueur en "pret"
 *
 * @param current_room salle d'attente
 * 
 * @param current_player joueur en cours
 * 
 * */

void RoomSetPlayerToReady(Room *current_room, Player *current_player)
{
    for (int i = 0; i < current_room->nb_player; i++)
    {
        Player *player = (current_room->players + i * sizeof(Player));
        if (player->id == current_player->id)
        {
            player->ready = true;
            break;
        }
    }
}

/**
 * Si tous les joueurs de la salle d'attente sont prets
 *
 * @param current_room salle d'attente
 * 
 * @return boolean
 * 
 * */

bool isRoomReady(Room *current_room)
{
    for (int i = 0; i < getMaxPlayerPerRoom(); i++)
    {
        Player *player = (current_room->players + i * sizeof(Player));
        if (player->ready == false)
            return false;
    }
    return true;
}
