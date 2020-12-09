#ifndef PARSER_H
#define PARSER_H

typedef struct
{
    char *server_ip_address;
    int server_port;
    int max_simultaneous_connection;
    int max_player_per_room;
} Config;

void ParseConfig(char *filename);
Config getConfig();
char *getServerIpAddress();
int getServerPort();
int getMaxSimultaneousConnection();
int getMaxPlayerPerRoom();

#endif /* PARSER_H */