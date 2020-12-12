#include "read.h"
#include "../serialization/serialize.h"
Packet *BufferRead(Room *current_room, Player *current_player, char *buffer_in, int buffer_size)
{
    return Deserialize(buffer_in, buffer_size);
}
