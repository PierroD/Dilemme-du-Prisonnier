/**
 * \file        write.c
 * \brief       Envoi donnees au serveur
 * */


#include "write.h"

int serverSocket = 0;

void setServerSocket(int value)
{
    serverSocket = value;
}

void BufferWrite(Packet *packet)
{
    write(serverSocket, packet, sizeof(Packet));
}