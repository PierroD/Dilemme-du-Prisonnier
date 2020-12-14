#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include "../../models/packetModel.h"
#include "../../models/gameModel.h"

void view_writeGameInfo(Game *game);
void view_writeRoundInfo(Round *round, int round_nb);
void view_writeAllRoundInfo(Round *round, int round_nb);
void view_writeDilemmaInfo(Dilemma *dilemma);
void view_writeAnswerInfo(Answer *answer);

#endif /* GAMEVIEW_H */