#ifndef GAME_H
#define GAME_H

#include <stdbool.h>
#include "room.h"
#include "../utils/bufferreader.h"
#include "../utils/serialize.h"

typedef struct {
    Player *players;
    int nb_rounds;
    int time_to_answer; // in seconds
    int punishement; // in years
    bool in_progress;
    Round *rounds;
}Game;

typedef struct {
    Choice *choices;
}Round;

typedef struct{
    int id_player;
    int choice; // init = -1; silent = 0; betray = 1;
    int time_to_decide;
}Choice;

#endif /* GAME_H */