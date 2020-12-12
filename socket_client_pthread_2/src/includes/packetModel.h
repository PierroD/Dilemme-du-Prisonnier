#ifndef PACKET_H
#define PACKET_H

enum action
{
    CONNECTED,
    PLAYER_READY,
    ROOM_READY,
    ASK_CHOICE,
    RESPONSE,
    GAME_END,
    DISCONNECT,
};

enum Decision
{
    SILENT,
    BETRAY
};

typedef struct
{
    int player_id;
    int choice; // init = -1; silent = 0; betray = 1;
    int bet;    // in years
    int time_to_decide;
} Answer;

typedef struct
{
    int punishement;
    int time_to_decide;
} Dilemma;

typedef struct
{
    enum action code;
    int size_data;
    char data[32];
} Packet;

#endif /* PACKET_H */