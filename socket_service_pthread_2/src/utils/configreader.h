#ifndef CONFIGREADER_H
#define CONFIGREADER_H

typedef struct
{
    char *server_ip_address;
    int server_port;
    int max_simultaneous_connection;
    int max_player_per_room;
} Config;

void parseConfig(char *filename);
Config getConfig();
char *getServerIpAddress();
int getServerPort();
int getMaxSimultaneousConnection();
int getMaxPlayerPerRoom();

#endif /* CONFIGREADER_H */