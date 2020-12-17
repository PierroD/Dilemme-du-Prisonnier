/**
 * \file        serialize.c
 * \brief       Envoie serialisé des packets
 * */


#include "serialize.h"

/**
 * deserialisation du buffer
 *
 * @param buffer_in buffer
 * 
 * @param buffer_size taille du buffer
 * 
 * @return un packet
 * 
 * */

Packet *Deserialize(char *buffer_in, int buffer_size)
{
    char packet_buffer[buffer_size];
    memcpy(packet_buffer, buffer_in, sizeof(Packet));
    Packet *packet = (Packet *)packet_buffer;
    return packet;
}

/**
 * Serialisation des données
 *
 * @param code type d'action du packet
 * 
 * @param object packet
 * 
 * @param object_size taille du packet
 * 
 * @return packet
 * 
 * */

Packet *SerializeData(enum action code , void* object, int object_size)
{
    Packet *packet = (Packet *)malloc(sizeof(Packet));
    packet->code = code;
    packet->size_data = sizeof(*object);
    memcpy(packet->data, (unsigned char *)object, object_size);
    return packet;
}

/**
 * Serialisation d'un message
 *
 * @param code type d'action du packet
 * 
 * @param message packet
 * 
 * @return packet
 * 
 * */

Packet *SerializeMessage(enum action code, char *message)
{
    Packet *packet = (Packet *)malloc(sizeof(Packet));
    packet->code = code;
    packet->size_data = strlen(message);
    memcpy(packet->data, (unsigned char*)message, packet->size_data);
    return packet;
}

