/**
 * \file        response.c
 * \brief       Gestion des reponses vers le client
 * */


#include <stdlib.h>
#include <sys/socket.h>
#include "response.h"
#include "../connection/manager.h"
#include "../../models/packetModel.h"
#include "../serialization/serialize.h"
#include "../buffer/write.h"

/**
 * Le joueur est connecté
 *
 * @param current_player joueur en cours
 * 
 * */

void response_PlayerIsConnected(Player *current_player)
{
    BufferWriteToClient(current_player, SerializeMessage(CONNECTED, "You are connected"));
}

/**
 * Le joueur est pret
 *
 * @param current_player joueur courant
 * 
 * */

void response_PlayerIsReady(Player *current_player)
{
    BufferWriteToClient(current_player, SerializeMessage(PLAYER_READY, "You are ready"));
}

/**
 * Tous les joueurs de la salle d'attente sont pret
 *
 * @param current_room salle d'attente
 * 
 * */

void response_RoomIsReady(Room *current_room)
{
    BufferWriteToRoom(current_room, SerializeMessage(ROOM_READY, "Your room is ready"));
}

/**
 * La fin de la partie
 *
 * @param current_room salle d'attente
 * 
 * */

void response_EndOfGame(Room *current_room)
{
    BufferWriteToRoom(current_room, SerializeMessage(GAME_END, "The game end"));
}
