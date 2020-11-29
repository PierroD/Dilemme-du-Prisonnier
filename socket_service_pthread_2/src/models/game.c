#include "game.h"

init_game(Game *game, Player *players)
{
    game = (Game *)calloc(getMaxSimultaneousConnection() / getMaxPlayerPerRoom(), sizeof(Game));
    memcpy(game->players, players, sizeof(Player *));
    game->nb_rounds = rand() % 10;           // remplacer par un élément du .ini (aléatoire entre 1 - 10)
    game->time_to_answer = rand() % 31 + 30; // remplacer par un élément du .ini (aléatoire entre 30 et 60)
    game->punishement = (rand()%10)*10 + 10 / game->nb_rounds; // nb année = multiple de DIX (compris entre 10 et 100) / nb_round
    game->in_progress = true;
    game->rounds = calloc(game->nb_rounds, sizeof(Round));
}

start_game(Room *current_room)
{
    Game *game = NULL;
    init_game(game, current_room->players);
    pthread_t gameThread;
    pthread_create(&gameThread, 0, gameThread, game);
    phtread_detach(gameThread);
}

void send_dilemma_to_players(Game *current_game)
{
    Dilemma *dilemma = calloc(1, sizeof(Dilemma));
    dilemma->punishement = current_game->punishement;
    dilemma->time_to_decide = current_game->time_to_answer;
    for (int i = 0; i < getMaxPlayerPerRoom(); i++)
    {   
        write_buffer_to_client((current_game->players + i * sizeof(Player)),serializeData(ASK_CHOICE, dilemma));
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

void *threadGame(void *gamePointer)
{
    Game *current_game;
    if (!gamePointer)
        pthread_exist(0);
    current_game = (Game *)gamePointer;

    int round_counter = 0;
    while (current_game->in_progress)
    {
        // send dilemma
        send_dilemma_to_players(current_game);
        if (current_game->nb_rounds - round_counter == -1)
            current_game->in_progress = false;
        else
        {

            Round *current_round = current_game->rounds + round_counter * sizeof(Round);
            if (isChoicesDone(current_round))
            {
                round_counter++;
                // send dilemma
                send_dilemma_to_players(current_game);

            }
        }
    }
    // enregister le resulat de la game
}
