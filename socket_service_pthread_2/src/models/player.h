#ifndef PLAYER_H
#define PLAYER_H

#include <stdbool.h>
#include "../srvcxnmanager.h"

typedef struct
{
    int id;
    bool in_room;
    int point;
    bool ready;
    connection_t *connection;
} Player;

Player *create_player(connection_t *connection);

#endif /* PLAYER_H */
