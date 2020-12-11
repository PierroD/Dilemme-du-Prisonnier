#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include "tocsv.h"
#include "../config/parser.h"
#include "../../models/packetModel.h"
#include "../../views/game/gameView.h"

char *getFilePath(int game_id, int filename_without_extension)
{
    char current_directory[FILENAME_MAX];
    char *filepath;
    if (getExportFolderPath() == 0x0)
    {
        asprintf(&filepath, "%s/%d-%d.csv", getcwd(current_directory, FILENAME_MAX), game_id, filename_without_extension);
    }
    else
        asprintf(&filepath, "%s/%d-%d.csv", getExportFolderPath(), game_id, filename_without_extension);

    return filepath;
}

void ExportGameToCSV(Game *game)
{
    Game *save = (Game *)malloc(sizeof(Game));
    memcpy(save, game, sizeof(Game));
    FILE *file;
    char *filepath = getFilePath(game->id_game, game->game_created_at);
    char *content;
    //     view_writeAllRoundInfo(game->rounds + 1 * sizeof(Round), 1, true);
    //     file = fopen(filepath, "w+");
    //     view_writeAllRoundInfo(game->rounds + 1 * sizeof(Round), 1, true);
    //     fprintf(file, "Round N°, Player ID, Choice, Bet, Time to Decide"); // Table header
    for (int i = 0; i < game->nb_rounds; i++)
    {
        Round *current_round = save->rounds + i * sizeof(Round);
        view_writeAllRoundInfo(current_round, i, true);
        for (int j = 0; j < getMaxPlayerPerRoom(); j++)
        {
            Answer *current_answer = current_round->answers + j * sizeof(Answer);
            view_writeAnswerInfo(current_answer, true);
            fprintf(file, "\n %d, %d, %s, %d, %d", i, current_answer->player_id, (current_answer->choice) ? "Betray" : "Silent", current_answer->bet, current_answer->time_to_decide);
        }
    }
    fclose(file);
}
