#ifndef GAME_H
#define GAME_H

#include <stdbool.h>
#include <pthread.h>
#include "room.h"
#include "player.h"
#include "../utils/bufferreader.h"
#include "../utils/configreader.h"
#include "../utils/serialize.h"


typedef struct{
    int id_player;
    int choice; // init = -1; silent = 0; betray = 1;
    int time_to_decide;
}Choice;

typedef struct {
    Choice *choices;
}Round;

typedef struct {
    Player *players;
    int nb_rounds;
    int time_to_answer; // in seconds
    int punishement; // in years
    bool in_progress;
    Round *rounds;
}Game;

void init_game(Game *game, Player *players);
void start_game(Room *current_room);
void send_dilemma_to_players(Game *current_game);
bool isChoicesDone(Round *current_round);
void threadGame(void *gamePointer);

#endif /* GAME_H */