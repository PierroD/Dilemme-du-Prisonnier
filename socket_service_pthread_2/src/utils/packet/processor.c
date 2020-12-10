#include "processor.h"
#include "../response/response.h"
#include "../../controllers/game/gameController.h"
#include "../../models/gameModel.h"
#include "../config/parser.h"

void PacketProcessor(Packet *packet, Room *current_room, Player *current_player)
{
    switch (packet->code)
    {
    case PLAYER_READY:
    {
        RoomSetPlayerToReady(current_room, current_player);
        if (isRoomReady(current_room))
        {
            response_RoomIsReady(current_room);
            sleep(1);
            GameStart(current_room);
        }
        else
            response_PlayerIsReady(current_player);

        break;
    }
    case RESPONSE:
    {
        char *serialize_answer;
        serialize_answer = packet->data;
        Answer *answer = (Answer *)serialize_answer;
        answer->player_id = current_player->id;
        AddChoiceToGame(current_room, answer, current_player->id % getMaxPlayerPerRoom());
        break;
    }
    }
}