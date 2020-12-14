#ifndef PACKET_H
#define PACKET_H

enum action{
    CONNECTED,
    PLAYER_READY,
    ROOM_READY,
    ASK_CHOICE,
    RESPONSE,
    GAME_END
};

enum choice{
    SILENT,
    BETRAY
};

typedef struct{
    int player_id;
    int bet;
    enum choice choice;
    int time_to_answer;
}Answer;

typedef struct{
    int punishement;
    int time_to_decide;
}Dilemma;

typedef struct {
    enum action code;
    int size_data;
    char data[32];
}Packet; 

#endif /* PACKET_H */