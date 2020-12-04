#include "game.h"

Game *games = NULL;

void init_game(Room *room)
{
    if (games == NULL)
        games = (Game *)calloc(getMaxSimultaneousConnection() / getMaxPlayerPerRoom(), sizeof(Game));
    Game *game = &games[room->id_room];
    game->players = room->players;
    game->id_game = room->id_room;
    game->nb_rounds = rand() % 10;                                 // remplacer par un élément du .ini (aléatoire entre 1 - 10)
    game->time_to_answer = rand() % 31 + 30;                       // remplacer par un élément du .ini (aléatoire entre 30 et 60)
    game->punishement = (rand() % 10) * 10 + 10 / game->nb_rounds; // nb année = multiple de DIX (compris entre 10 et 100) / nb_round
    game->in_progress = true;
    game->round_counter = 0;
    game->rounds = (Round *)malloc(game->nb_rounds * sizeof(Round));
}

void start_game(Room *current_room)
{
    printf("la partie commence\n");
    init_game(current_room);
    init_round(&games[current_room->id_room], current_room);
}

void send_dilemma_to_players(Game *current_game)
{
    Dilemma *dilemma = (Dilemma *)calloc(1, sizeof(Dilemma));
    dilemma->punishement = current_game->punishement;
    dilemma->time_to_decide = current_game->time_to_answer;
    for (int i = 0; i < getMaxPlayerPerRoom(); i++)
    {
        write_buffer_to_client((current_game->players + i * sizeof(Player)), serializeData(ASK_CHOICE, dilemma, sizeof(dilemma)));
    }
}

bool isChoicesDone(Round *current_round)
{
    for (int i = 0; i < getMaxPlayerPerRoom(); i++)
    {
        Choice *player_choice = (current_round->choices + i * sizeof(Choice));
        if (player_choice->choice == -1)
            return false;
    }
    return true;
}

void init_round(Game *current_game, Room *current_room)
{
    if (current_game->in_progress)
    {
        if (current_game->nb_rounds - current_game->round_counter == -1)
        {
            current_game->in_progress = false;
            response_EndOfGame(current_room);
        }
        else
        {
            Round *current_round = current_game->rounds + current_game->round_counter * sizeof(Round);
            send_dilemma_to_players(current_game);
            current_round->choices = (Choice *)malloc(getMaxPlayerPerRoom() * sizeof(Choice));
        }
    }
    // enregister le resulat de la game
}

void addChoiceToGame(Room *current_room, void *choice)
{
    Game *current_game = &games[current_room->id_room];
    Choice *current_choice = (Choice *)choice;
    memcpy(current_game->rounds[current_game->round_counter].choices, current_choice, sizeof(Choice));
    CheckNextRound(current_game, current_room);
}

void CheckNextRound(Game *current_game, Room *current_room)
{
    Round *current_round = &current_game->rounds[current_game->round_counter];
    if (isChoicesDone(current_round))
    {
        current_game->round_counter++;
        // write result in a file
        init_round(current_game, current_room);
    }
}