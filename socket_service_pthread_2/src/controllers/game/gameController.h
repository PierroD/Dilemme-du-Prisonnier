#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include "../../models/roomModel.h"
#include "../../models/playerModel.h"
#include "../../models/packetModel.h"
#include "../../models/gameModel.h"

void GameInitialize(Room *room);
void GameStart(Room *current_room);
void SendDilemmaToPlayer(Game *current_game);
bool isChoicesDone(Round *current_round);
void RoundInitialize(Game *current_game, Room *current_room);
void AddChoiceToGame(Room *current_room, Answer *current_choice, int answer_index);
void CheckNextRound(Game *current_game, Room *current_room, Round *current_round);
#endif /* GAMECONTROLLER_H */