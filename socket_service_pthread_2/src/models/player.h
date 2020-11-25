#ifndef PLAYER_H
#define PLAYER_H

#include "../srvcxnmanager.h"

#define true 1
#define false 0

typedef struct {
    int id;
    int in_room;
    int point;
    int ready;
    connection_t* connection;
} Player;

Player *create_player(connection_t *connection);

#endif /* PLAYER_H */
