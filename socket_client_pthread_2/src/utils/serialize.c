#include "serialize.h"

Packet *deserialize(char *buffer_in, int buffer_size)
{
    char temp_buffer[buffer_size];
    memcpy(temp_buffer, buffer_in, sizeof(Packet));
    Packet *packet = (Packet *)temp_buffer;
    return packet;
}

Packet *serializeData(enum action code , void* object, int object_size)
{
    Packet *packet = (Packet *)malloc(sizeof(Packet));
    packet->code = code;
    packet->size_data = sizeof(*object);
    memcpy(packet->data, (unsigned char *)object, object_size);
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
