#ifndef PACKET_H
#define PACKET_H

enum action{
    CONNECTED,
    PLAYER_READY,
    ROOM_READY,
    ASK_CHOICE, 
    GAME_END
};

enum choice{
    SILENT,
    BETRAY
};


typedef struct{
    int player_id;
    int punishement;
    int time_to_decide;
}Dilemma;

typedef struct {
    enum action code;
    int size_data;
    char data[32];
}Packet; 

#endif /* PACKET_H */