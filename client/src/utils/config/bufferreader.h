#ifndef BUFFERREADER_H
#define BUFFERREADER_H
#define BUFFERSIZE 2048

// TODO :en avoir le minimum
#include <stdbool.h>
#include "../includes/packet.h"
#include "serialize.h"
#include "packetprocessor.h"

void read_buffer(char *buffer_in, int buffer_size);
void write_buffer(int serverSocket, Packet *packet);
#endif /* BUFFERREADER_H */
