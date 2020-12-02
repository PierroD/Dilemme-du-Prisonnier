#include "bufferreader.h"


void read_buffer(char buffer_in[], int buffer_size){
    Packet *packet = deserialize(buffer_in, buffer_size);
    printf("%2X \n", buffer_in);
    printf("data : %s \n", packet->data);
}

void write_buffer(int serverSocket, Packet *packet)
{
    write(serverSocket, packet, sizeof(Packet));
}
