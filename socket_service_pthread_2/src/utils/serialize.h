#ifndef SERIALIZE_H
#define SERIALIZE_H

#include "../includes/packet.h"

Packet *deserialize(char *buffer_in, char *buffer_size);
Packet *serializeData(enum action code , void* object);
Packet *serializeMessage(enum action code, char *message);
#endif /* SERIALIZE_H */