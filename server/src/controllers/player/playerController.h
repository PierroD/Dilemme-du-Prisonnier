#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H

#include <stdbool.h>
#include "../../utils/connection/manager.h"
#include "../../models/playerModel.h"

Player *PlayerCreate(connection_t *connection);

#endif /* PLAYERCONTROLLER_H */
