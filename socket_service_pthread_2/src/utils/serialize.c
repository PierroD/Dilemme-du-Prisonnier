#include "serialize.h"

Packet *deserialize(char *buffer_in, char *buffer_size)
{
    Packet *packet = (Packet *)buffer_in;
    return packet;
}

Packet *serializeData(enum action code , void* object)
{
    Packet *packet = (Packet *)malloc(sizeof(Packet));
    packet->code = code;
    packet->size_data = sizeof(*object);
    memcpy(packet->data, (unsigned char)object, sizeof(*object));
    return packet;
}

Packet *serializeMessage(enum action code, char *message)
{
    Packet *packet = (Packet *)malloc(sizeof(Packet));
    packet->code = code;
    packet->size_data = strlen(message);
    memcpy(packet->data, (unsigned char*)message, packet->size_data);
    return packet;
}