/**
 * \file        read.c
 * \brief       Reception donnees recus par le serveur
 * */


#include "read.h"
#include "../serialization/serialize.h"
Packet *BufferRead(char *buffer_in, int buffer_size)
{
    return Deserialize(buffer_in, buffer_size);
}
