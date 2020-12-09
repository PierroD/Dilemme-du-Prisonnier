#include <stdbool.h>
#include <pthread.h>
#include "gameController.h"
#include "../../utils/buffer/write.h"
#include "../../utils/config/parser.h"
#include "../../utils/serialization/serialize.h"

Game *games = NULL;

void GameInitialize(Room *room)
{
    if (games == NULL)
        games = (Game *)calloc(getMaxSimultaneousConnection() / getMaxPlayerPerRoom(), sizeof(Game));
    Game *game = (games + room->id_room * sizeof(Game));
    game->players = room->players;
    game->id_game = room->id_room;
    game->nb_rounds = rand() % 10; // remplacer par un élément du .ini (aléatoire entre 1 - 10)
    printf("nb rounds : %d\n", game->nb_rounds);
    game->time_to_answer = rand() % 31 + 30;   // remplacer par un élément du .ini (aléatoire entre 30 et 60)
    game->punishement = 100 / game->nb_rounds; // nb année = multiple de DIX (compris entre 10 et 100) / nb_round
    game->in_progress = true;
    game->round_counter = 0;
    game->rounds = (Round *)malloc(game->nb_rounds * sizeof(Round));
}

void GameStart(Room *current_room)
{
    printf("la partie commence\n");
    GameInitialize(current_room);
    RoundInitialize((games + current_room->id_room * sizeof(Game)), current_room);
}

void SendDilemmaToPlayer(Game *current_game)
{
    Dilemma *dilemma = (Dilemma *)calloc(1, sizeof(Dilemma));
    dilemma->punishement = current_game->punishement;
    dilemma->time_to_decide = current_game->time_to_answer;
    for (int i = 0; i < getMaxPlayerPerRoom(); i++)
    {
        BufferWriteToClient((current_game->players + i * sizeof(Player)), SerializeData(ASK_CHOICE, dilemma, sizeof(dilemma)));
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

void RoundInitialize(Game *current_game, Room *current_room)
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
            SendDilemmaToPlayer(current_game);
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

void AddChoiceToGame(Room *current_room, Answer *player_answer)
{
    Game *current_game = (games + current_room->id_room * sizeof(Game));
    Round *current_round = (current_game->rounds + current_game->round_counter * sizeof(Round));
    int player_id = player_answer->player_id;
    Answer *current_answer = (current_round->answers + (player_id - (1 + ((current_room->id_room - 1) * getMaxPlayerPerRoom()))) * sizeof(Answer));
    //Answer *answers = current_round->answers;
   // current_answer = player_answer;
    memcpy(current_answer, player_answer, (Answer *)sizeof(Answer));
    CheckNextRound(current_game, current_room, current_round);
}

void CheckNextRound(Game *current_game, Room *current_room, Round *current_round)
{
    if (isChoicesDone(current_round))
    {
        current_game->round_counter++;
        // write result in a file
        RoundInitialize(current_game, current_room);
    }
}