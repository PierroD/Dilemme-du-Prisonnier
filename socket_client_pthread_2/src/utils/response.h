#ifndef RESPONSE_H
#define RESPONSE_H
#include <stdlib.h>
#include <sys/socket.h>
#include "../clientcxnmanager.h"
#include "../includes/packet.h"
#include "../utils/serialize.h"
#include "../utils/bufferreader.h"

void response_PlayerIsReady();
void response_PlayerAnswer(Answer *answer);
#endif /* RESPONSE_H */