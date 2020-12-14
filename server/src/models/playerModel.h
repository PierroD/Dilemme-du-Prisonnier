#ifndef PLAYERMODEL_H
#define PLAYERMODEL_H

#include <stdbool.h>
#include "../utils/connection/manager.h"

typedef struct
{
    int id;
    bool in_room;
    int point;
    bool ready;
    connection_t *connection;
} Player;

#endif /* PLAYERMODEL_H */