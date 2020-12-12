#ifndef GAMEMODEL_H
#define GAMEMODEL_H

#include "playerModel.h"
#include "packetModel.h"

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
    int game_created_at; // timestamp
    Round *rounds;
} Game;

#endif /* GAMEMODEL_H */