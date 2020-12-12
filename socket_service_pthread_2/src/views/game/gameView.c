#include "gameView.h"
#include "../offset/offsetView.h"
#include "../../utils/config/parser.h"
// TODO if pour config debug
void view_writeGameInfo(Game *game)
{
    if (getShowGame())
    {
        printf("\033[1;31m GAME \033[0mGame ID \033[0;32m%d \033[0mnumber of rounds \033[0;32m%d \033[0mtime to answer \033[0;32m%d \033[0mpunishement \033[0;32m%d \033[0mcurrent round \033[0;32m%d \033[0m\n", game->id_game, game->nb_rounds, game->time_to_answer, game->punishement, game->round_counter);
        writeOffset(game);
    }
}

void view_writeRoundInfo(Round *round, int round_nb)
{
    if (getShowRound())
    {
        printf("\033[1;33m ROUND \033[0mnumber \033[0;32m%d \033[0m\n", round_nb);
        writeOffset(round);
    }
}

void view_writeDilemmaInfo(Dilemma *dilemma)
{
    if (getShowDilemma())
    {
        printf("\033[1;33m DILEMMA \033[0mpunishement \033[0;32m%d \033[0mtime to decide \033[0;32m%d\033[0m\n", dilemma->punishement, dilemma->time_to_decide);
        writeOffset(dilemma);
    }
}

void view_writeAnswerInfo(Answer *answer)
{
    if (getShowAnswer())
    {
        printf("\033[1;33m ANSWER \033[0mplayer ID \033[0;32m%d \033[0mchoice \033[0;32m%s \033[0mbet \033[0;32m%d \033[0mtime to decide \033[0;32m%d \033[0m\n", answer->player_id, (answer->choice) ? "BETRAY" : "SILENT", answer->bet, answer->time_to_decide);
        writeOffset(answer);
    }
}
