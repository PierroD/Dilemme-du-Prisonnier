#include "packetprocessor.h"

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
        newDilemma(dilemma->time_to_decide, dilemma->punishement);
        break;
    }
    }
}