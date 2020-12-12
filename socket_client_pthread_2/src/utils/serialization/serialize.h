#ifndef SERIALIZE_H
#define SERIALIZE_H

#include "../../includes/packetModel.h"

Packet *Deserialize(char *buffer_in, int buffer_size);
Packet *SerializeData(enum action code, void *object, int object_size);
Packet *SerializeMessage(enum action code, char *message);
#endif /* SERIALIZE_H */