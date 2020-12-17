/**
 * \file        processor.c
 * \brief       Traitement du packet recu (packetModel.h)
 * */


#include "processor.h"
#include "../response/response.h"
#include "../../controllers/game/gameController.h"
#include "../../views/packet/packetView.h"
#include "../../models/gameModel.h"
#include "../config/parser.h"

/**
 * Determine l'action du serveur en fonction du packet recu
 *
 * @param packet packet recu
 * 
 * @param current_room salle d'attente
 * 
 * @param current_player joueur courant
 * 
 * */

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
    case DISCONNECT:
    {
        close(current_player->connection->sockfd);
        free(current_player->connection);
    }
    }
}