#include "bufferreader.h"

int serverSocket=0;

void read_buffer(char buffer_in[], int buffer_size)
{
    Packet *packet = deserialize(buffer_in, buffer_size);
    process_packet(packet);
}

void write_buffer(Packet *packet)
{
    write(serverSocket, packet, sizeof(Packet));
}

void set_ServerScoket(int value)
{
    serverSocket = value;
}