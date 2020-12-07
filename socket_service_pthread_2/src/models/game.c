#include "game.h"

Game *games = NULL;

void init_game(Room *room)
{
    if (games == NULL)
        games = (Game *)calloc(getMaxSimultaneousConnection() / getMaxPlayerPerRoom(), sizeof(Game));
    Game *game = &games[room->id_room];
    game->players = room->players;
    game->id_game = room->id_room;
    game->nb_rounds = rand() % 10;             // remplacer par un élément du .ini (aléatoire entre 1 - 10)
    printf("nb rounds : %d\n", game->nb_rounds);
    game->time_to_answer = rand() % 31 + 30;   // remplacer par un élément du .ini (aléatoire entre 30 et 60)
    game->punishement = 100 / game->nb_rounds; // nb année = multiple de DIX (compris entre 10 et 100) / nb_round
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
        Answer *player_choice = (current_round->answers + i * sizeof(Answer));
        if (player_choice->choice == -1)
            return false;
    }
    return true;
}

void init_round(Game *current_game, Room *current_room)
{
    if (current_game->in_progress)
    {
        if (current_game->nb_rounds - current_game->round_counter == 0)
        {
            current_game->in_progress = false;
            response_EndOfGame(current_room);
        }
        else
        {
            Round *current_round = current_game->rounds + current_game->round_counter * sizeof(Round);
            send_dilemma_to_players(current_game);
            current_round->answers = (Answer *)malloc(getMaxPlayerPerRoom() * sizeof(Answer));
            init_choices(current_round->answers);
        }
    }
    // enregister le resulat de la game
}

void init_choices(Answer *answers)
{
    for (int i = 0; i < getMaxPlayerPerRoom(); i++)
    {
        (answers + i * sizeof(Answer))->choice = -1;
    }
}

void addChoiceToGame(Room *current_room, void *choice)
{
    Game *current_game = &games[current_room->id_room];
    Answer *current_choice = (Answer *)choice;
    Round *current_round = (current_game->rounds + current_game->round_counter * sizeof(Round));
    //Answer *answers = current_round->answers;
    memcpy((current_round->answers + (current_choice->player_id - 1) * sizeof(Answer)), current_choice, sizeof(Answer));
    CheckNextRound(current_game, current_room, current_round);
}

void CheckNextRound(Game *current_game, Room *current_room, Round *current_round)
{
    if (isChoicesDone(current_round))
    {
        current_game->round_counter++;
        // write result in a file
        init_round(current_game, current_room);
    }
}