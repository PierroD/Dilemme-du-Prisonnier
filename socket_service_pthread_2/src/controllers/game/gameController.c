#include <stdbool.h>
#include <pthread.h>
#include "gameController.h"
#include "../../utils/buffer/write.h"
#include "../../utils/config/parser.h"
#include "../../utils/serialization/serialize.h"
#include "../../utils/export/tocsv.h"
#include "../../views/game/gameView.h"

Game *games = NULL;

void GameInitialize(Room *room)
{
    if (games == NULL)
        games = (Game *)calloc(getMaxSimultaneousConnection() / getMaxPlayerPerRoom(), sizeof(Game));
    Game *game = (games + room->id_room * sizeof(Game));
    game->players = room->players;
    game->id_game = room->id_room;
    game->nb_rounds = 2; //rand() % 10; // remplacer par un élément du .ini (aléatoire entre 1 - 10)
    printf("nb rounds : %d\n", game->nb_rounds);
    game->time_to_answer = rand() % 31 + 30;   // remplacer par un élément du .ini (aléatoire entre 30 et 60)
    game->punishement = 100 / game->nb_rounds; // nb année = multiple de DIX (compris entre 10 et 100) / nb_round
    game->in_progress = true;
    game->round_counter = 0;
    game->game_created_at = (int)time(NULL);
    game->rounds = (Round *)malloc(game->nb_rounds * sizeof(Round));
    view_writeGameInfo(game, true);
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
    view_writeDilemmaInfo(dilemma, true);
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
            // view_writeAllRoundInfo(current_game->rounds + 0 * sizeof(Round), 0, true);
            ExportGameToCSV(current_game);
            response_EndOfGame(current_room);
        }
        else
        {
            Round *current_round = current_game->rounds + current_game->round_counter * sizeof(Round);
            SendDilemmaToPlayer(current_game);
            current_round->answers = (Answer *)malloc(getMaxPlayerPerRoom() * sizeof(Answer));
            view_writeRoundInfo(current_round, current_game->round_counter, true);
            GameChoicesInitialize(current_round->answers);
        }
    }
}

void GameChoicesInitialize(Answer *answers)
{
    for (int i = 0; i < getMaxPlayerPerRoom(); i++)
    {
        (answers + i * sizeof(Answer))->choice = -1;
    }
}

void AddChoiceToGame(Room *current_room, Answer *player_answer, int answer_index)
{
    Game *current_game = (games + current_room->id_room * sizeof(Game));
    Round *current_round = (current_game->rounds + current_game->round_counter * sizeof(Round));
    Answer *current_answer = (current_round->answers + answer_index * sizeof(Answer));
    memcpy(current_answer, player_answer, sizeof(Answer));
    view_writeAnswerInfo(current_answer, true);
    CheckNextRound(current_game, current_room, current_round);
}

void CheckNextRound(Game *current_game, Room *current_room, Round *current_round)
{
    if (isChoicesDone(current_round))
    {
        current_game->round_counter++;
        RoundInitialize(current_game, current_room);
    }
}
