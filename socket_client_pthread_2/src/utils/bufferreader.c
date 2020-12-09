#include "bufferreader.h"
#include "serialize.h"

int serverSocket = 0;

Packet *read_buffer(char buffer_in[], int buffer_size)
{
    return deserialize(buffer_in, buffer_size);
}

void write_buffer(Packet *packet)
{
    write(serverSocket, packet, sizeof(Packet));
}

void set_ServerScoket(int value)
{
    serverSocket = value;
}