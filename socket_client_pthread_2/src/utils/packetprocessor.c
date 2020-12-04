#include "packetprocessor.h"

void process_packet(Packet *packet)
{
    switch (packet->code)
    {
    case CONNECTED:
    {
        setButtonReadyToVisible();// set ready btn visible
        break;
    }
    case ROOM_READY:
    {
        printf("your room is ready\n"); // lancer l'interface pour jouer
        break;
    }
    case ASK_CHOICE:
    {
        Dilemma *dilemma = (Dilemma *)packet->data;
        printf("dilem recupéré\n");
        break;
    }

    }
}