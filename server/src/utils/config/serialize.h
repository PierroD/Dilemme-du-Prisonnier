#ifndef SERIALIZE_H
#define SERIALIZE_H

#include "../includes/packet.h"

Packet *deserialize(char *buffer_in);
Packet *serializeData(enum action code , void* object, int object_size);
Packet *serializeMessage(enum action code, char *message);
#endif /* SERIALIZE_H */