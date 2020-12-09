#include "packetprocessor.h"
#include "../controller/gameWindowController.h"

void process_packet(Packet *packet)
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
        printf("PLAYER READY\n");
        setlblStatusText("En attente d'acceptation des autres joueurs");
        setButtonReadyVisible(false);
        break;
    }
    case ROOM_READY:
    {
        printf("ROOM READY\n");
        showHideGameWindow(true);
        break;
    }
    case ASK_CHOICE:
    {
        printf("REVCEIVE DILEMMA\n");
        Dilemma *dilemma = (Dilemma *)packet->data;
        sleep(1);
        newDilemma(dilemma->time_to_decide, dilemma->punishement);
        break;
    }
    case GAME_END:
    {
        printf("GAME END\n");
        setLblEventsText("The game is over");
        break;
    }
    }
}