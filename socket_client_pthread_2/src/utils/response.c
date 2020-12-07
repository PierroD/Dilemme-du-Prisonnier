#include "response.h"

void response_PlayerIsReady()
{
   write_buffer(serializeMessage(PLAYER_READY, "Player is ready")); // ADD TO RESPONSE
}


void response_PlayerAnswer(Answer *answer)
{
   write_buffer(serializeData(RESPONSE, answer, sizeof(Answer))); // ADD TO RESPONSE
}