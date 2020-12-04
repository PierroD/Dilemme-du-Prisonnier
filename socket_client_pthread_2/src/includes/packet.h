#ifndef PACKET_H
#define PACKET_H

enum action{
    CONNECTED,
    PLAYER_READY,
    WAITING,
    ROOM_READY,
    ASK_CHOICE,
    RESPONSE,
    GAME_END
};

typedef enum {
	SILENT,
	BETRAY
}Choice;

typedef struct{
    int player_id;
    int bet;
    Choice choice;
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