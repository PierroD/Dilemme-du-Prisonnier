#ifndef ROOMMODEL_H
#define ROOMMODEL_H

#include "playerModel.h"

typedef struct
{
    int id_room;
    int nb_player;
    Player *players;
} Room;

#endif /* ROOMMODEL_H */