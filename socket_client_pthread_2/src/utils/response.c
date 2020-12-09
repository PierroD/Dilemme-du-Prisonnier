#include <stdlib.h>
#include <sys/socket.h>
#include "response.h"
#include "../utils/serialize.h"
#include "../utils/bufferreader.h"
#include "../clientcxnmanager.h"
void response_PlayerIsReady()
{
   write_buffer(serializeMessage(PLAYER_READY, "Player is ready")); // ADD TO RESPONSE
}

void response_PlayerAnswer(Answer *answer)
{
   write_buffer(serializeData(RESPONSE, answer, sizeof(Answer))); // ADD TO RESPONSE
}