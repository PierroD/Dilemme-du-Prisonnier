#include <stdlib.h>
#include <sys/socket.h>
#include "response.h"
#include "../serialization/serialize.h"
#include "../buffer/write.h"
#include "../connection/manager.h"

void response_PlayerIsReady()
{
   BufferWrite(SerializeMessage(PLAYER_READY, "Player is ready")); // ADD TO RESPONSE
}

void response_PlayerAnswer(Answer *answer)
{
   BufferWrite(SerializeData(RESPONSE, answer, sizeof(Answer))); // ADD TO RESPONSE
}

void response_PlayerDisconnect()
{
   BufferWrite(SerializeMessage(DISCONNECT, "Player Disconnected"));
}