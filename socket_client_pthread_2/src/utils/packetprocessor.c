#include "packetprocessor.h"

void process_packet(Packet *packet)
{
    switch (packet->code)
    {
    case ROOM_READY:
    {
        printf("your room is ready\n");
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