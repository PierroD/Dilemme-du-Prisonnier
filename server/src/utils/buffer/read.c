/**
 * \file        read.c
 * \brief       Lire le buffer
 * */


#include "read.h"
#include "../serialization/serialize.h"

/**
 * Lit le buffer
 *
 * @param current_room salle d'attente
 * 
 * @param current_player un joueur
 * 
 * @param buffer_in buffer
 * 
 * @param buffer_size taille du buffer
 * 
 * @return packet
 * 
 * */

Packet *BufferRead(Room *current_room, Player *current_player, char *buffer_in, int buffer_size)
{
    return Deserialize(buffer_in, buffer_size);
}
