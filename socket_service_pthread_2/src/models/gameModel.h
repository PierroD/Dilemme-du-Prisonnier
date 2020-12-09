#ifndef GAMEMODEL_H
#define GAMEMODEL_H

#include "playerModel.h"
#include "playerModel.h"

typedef struct
{
    Answer *answers;
} Round;

typedef struct
{
    Player *players;
    int id_game;
    int nb_rounds;
    int time_to_answer; // in seconds
    int punishement;    // in years
    bool in_progress;
    int round_counter;
    Round *rounds;
} Game;

#endif /* GAMEMODEL_H */