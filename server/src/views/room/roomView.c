/**
 * \file        roomView.c
 * \brief       Visualisation de la salle d'attente
 * */
 

#include <arpa/inet.h>
#include "roomView.h"
#include "../../utils/connection/manager.h"
#include "../../utils/config/parser.h"

/**
 * Ecrit les informations d'un joueur
 *
 * @param player joueur
 * 
 * */

void view_writePlayerInfo(Player *player)
{
    if (getShowPlayer())
    {
        printf("\033[1;37m PLAYER \033[0mplayer ID \033[0;32m%d \033[0mplayer socket \033[0;32m%d \033[0min room \033[0;32m%d \033[0mready \033[0;32m%d \033[0m\n", player->id, player->connection->sockfd, player->in_room, player->ready);
        writeOffset(player);
    }
}

/**
 * Ecrit les information de la salle d'attente
 *
 * @param room salle d'attente
 * 
 * */

void view_writeRoomInfo(Room *room)
{
    if (getShowRoom())
    {
        printf("\033[1;37m ROOM \033[0mroom ID \033[0;32m%d \033[0mnumber of players \033[0;32m%d \033[0m\n", room->id_room, room->nb_player);
        writeOffset(room);
    }
}
