#ifndef PACKET_H
#define PACKET_H

enum action{
    CONNECTED,
    PLAYER_READY,
    ROOM_READY
};

enum choice{
    SILENT,
    BETRAY
};

typedef struct {
    char text[32];
    enum choice code;
}test;


typedef struct {
    enum action code;
    int size_data;
    char data[32];
}Packet; 

#endif /* PACKET_H */