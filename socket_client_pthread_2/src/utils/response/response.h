#ifndef RESPONSE_H
#define RESPONSE_H

#include "../../includes/packetModel.h"

void response_PlayerIsReady();
void response_PlayerAnswer(Answer *answer);
void response_PlayerDisconnect();
#endif /* RESPONSE_H */