#include <stdlib.h>
#include <sys/socket.h>

#include "player.h"

Player *create_player(connection_t *connection)
{
    Player *player = calloc(1,sizeof(Player));
    player->id = connection->index;
    player->connection = connection;
    return player;
}
