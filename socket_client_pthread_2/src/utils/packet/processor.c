#include "processor.h"
#include "../../controller/gameWindowController.h"

void PacketProcessor(Packet *packet)
{
    switch (packet->code)
    {
    case CONNECTED:
    {
        setlblStatusText("Vous êtes connecté");
        setButtonReadyVisible(true);
        break;
    }
    case PLAYER_READY:
    {
        setlblStatusText("En attente d'acceptation des autres joueurs");
        setButtonReadyVisible(false);
        break;
    }
    case ROOM_READY:
    {
        showHideGameWindow(true);
        showOrHideChoices(false);
        break;
    }
    case ASK_CHOICE:
    {
        Dilemma *dilemma = (Dilemma *)packet->data;
        newDilemma(dilemma->time_to_decide, dilemma->punishement);
        break;
    }
    case GAME_END:
    {
        setLblEventsText("La partie est terminée");
        break;
    }
    }
}