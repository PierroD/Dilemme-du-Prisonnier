#include "gameView.h"
#include "../offset/offsetView.h"
#include "../../utils/config/parser.h"

void view_writeGameInfo(Game *game, bool show_offsets)
{
    printf("\033[1;31m GAME \033[0mGame ID \033[0;32m%d \033[0mnumber of rounds \033[0;32m%d \033[0mtime to answer \033[0;32m%d \033[0mpunishement \033[0;32m%d \033[0mcurrent round \033[0;32m%d \033[0m\n", game->id_game, game->nb_rounds, game->time_to_answer, game->punishement, game->round_counter);
    if (show_offsets)
        writeOffset(game);
}

void view_writeRoundInfo(Round *round, int round_nb, bool show_offsets)
{
    printf("\033[1;33m ROUND \033[0mnumber \033[0;32m%d \033[0m\n", round_nb);
    if (show_offsets)
        writeOffset(round);
}

void view_writeAllRoundInfo(Round *round, int round_nb, bool show_offsets)
{
    printf("Round----%d----\n", round_nb);
    for (int i = 0; i < getMaxPlayerPerRoom(); i++)
    {
        view_writeAnswerInfo(round->answers + i * sizeof(Answer), show_offsets);
    }
    if (show_offsets)
    {
        printf("Round Offset----\n");
        writeOffset(round);
    }
    printf("---------\n");
}

void view_writeDilemmaInfo(Dilemma *dilemma, bool show_offsets)
{
    printf("\033[1;33m DILEMMA \033[0mpunishement \033[0;32m%d \033[0mtime to decide \033[0;32m%d\033[0m\n", dilemma->punishement, dilemma->time_to_decide);
    if (show_offsets)
        writeOffset(dilemma);
}

void view_writeAnswerInfo(Answer *answer, bool show_offsets)
{
    printf("\033[1;33m ANSWER \033[0mplayer ID \033[0;32m%d \033[0mchoice \033[0;32m%s \033[0mbet \033[0;32m%d \033[0mtime to decide \033[0;32m%d \033[0m\n", answer->player_id, (answer->choice) ? "BETRAY" : "SILENT", answer->bet, answer->time_to_decide);
    if (show_offsets)
        writeOffset(answer);
}
