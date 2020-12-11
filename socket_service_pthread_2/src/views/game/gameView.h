#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <stdbool.h>
#include "../../models/packetModel.h"
#include "../../models/gameModel.h"

void view_writeGameInfo(Game *game, bool show_offsets);
void view_writeRoundInfo(Round *round, int round_nb, bool show_offsets);
void view_writeAllRoundInfo(Round *round, int round_nb, bool show_offsets);
void view_writeDilemmaInfo(Dilemma *dilemma, bool show_offsets);
void view_writeAnswerInfo(Answer *answer, bool show_offsets);

#endif /* GAMEVIEW_H */