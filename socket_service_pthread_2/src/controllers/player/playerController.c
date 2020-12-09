#include <stdlib.h>
#include <sys/socket.h>
#include "playerController.h"

Player *PlayerCreate(connection_t *connection)
{
    Player *player = calloc(1, sizeof(Player));
    player->id = connection->index;
    player->connection = connection;
    return player;
}
