#ifndef BUFFERREADER_H
#define BUFFERREADER_H

// TODO :en avoir le minimum
#include <stdbool.h>
#include "../includes/packet.h"
#include "serialize.h"
#include "packetprocessor.h"

void set_ServerScoket(int value);
void read_buffer(char *buffer_in, int buffer_size);
void write_buffer(Packet *packet);

#endif /* BUFFERREADER_H */
