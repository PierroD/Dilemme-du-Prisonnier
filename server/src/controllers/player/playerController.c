/**
 * \file        playerController.c
 * \brief       Controleur des joueurs
 * */


#include <stdlib.h>
#include <sys/socket.h>
#include "playerController.h"


/**
 * Creation d'un joueur
 *
 * @param connection structure qui possède les attributs de connexion d'un joueur
 *
 * @return un joueur
 *  
 * */

Player *PlayerCreate(connection_t *connection)
{
    Player *player = calloc(1, sizeof(Player));
    player->id = connection->index;
    player->connection = connection;
    return player;
}
