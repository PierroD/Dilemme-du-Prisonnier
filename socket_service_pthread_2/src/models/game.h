#ifndef GAME_H
#define GAME_H

#include "room.h"
#include "player.h"
#include "../includes/packet.h"

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

void init_game(Room *room);
void start_game(Room *current_room);
void send_dilemma_to_players(Game *current_game);
bool isChoicesDone(Round *current_round);
void init_round(Game *current_game, Room *current_room);
void addChoiceToGame(Room *current_room, void *choice);
void CheckNextRound(Game *current_game, Room *current_room, Round *current_round);
#endif /* GAME_H */