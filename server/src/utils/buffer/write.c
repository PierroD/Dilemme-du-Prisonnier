/**
 * \file        write.c
 * \brief       Ecrire dans le buffer
 * */


#include "write.h"
#include "../../views/packet/packetView.h"

/**
 * Permet d'envoyer un message dans une salle d'attente
 *
 * @param current_room salle d'attente
 * 
 * @param packet packet à envoyer
 * 
 * */

void BufferWriteToRoom(Room *current_room, Packet *packet)
{
    for (int i = 0; i < current_room->nb_player; i++)
        BufferWriteToClient((current_room->players + i * sizeof(Player)), packet); //
}

/**
 * Permet d'envoyer un message a un joueur
 *
 * @param current_player joueur courant
 * 
 * @param packet packet à envoyer
 * 
 * */

void BufferWriteToClient(Player *current_player, Packet *packet)
{
    view_writePacketSentInfo(packet, current_player->id);
    BufferWrite(current_player->connection->sockfd, packet);
}

/**
 * Ecrire dans le buffer
 *
 * @param playerSocket socket du joueur courant
 * 
 * @param packet packet à envoyer
 * 
 * */

void BufferWrite(int playerSocket, Packet *packet)
{
    write(playerSocket, packet, sizeof(Packet));
}