#ifndef PARSER_H
#define PARSER_H

#include <stdbool.h>

typedef struct
{
    char *server_ip_address;
    int server_port;
    int max_simultaneous_connection;
    int max_player_per_room;
    int round_number;
    int time_to_decide;
    char *export_folder_path;
    bool show_packet;
    bool show_player;
    bool show_room;
    bool show_game;
    bool show_round;
    bool show_dilemma;
    bool show_answer;
    bool show_offset;
} Config;

void ParseConfig(char *filename);
Config getConfig();
char *getServerIpAddress();
int getServerPort();
int getMaxSimultaneousConnection();
int getMaxPlayerPerRoom();
int getRoundNumber();
int getTimeToDecide();
char *getExportFolderPath();
bool getShowPacket();
bool getShowPlayer();
bool getShowRoom();
bool getShowGame();
bool getShowRound();
bool getShowDilemma();
bool getShowAnswer();
bool getShowOffset();

#endif /* PARSER_H */