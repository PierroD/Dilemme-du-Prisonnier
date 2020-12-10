#ifndef PARSER_H
#define PARSER_H

typedef struct
{
    char *server_ip_address;
    int server_port;
    int max_simultaneous_connection;
    int max_player_per_room;
    char *export_folder_path;
} Config;

void ParseConfig(char *filename);
Config getConfig();
char *getServerIpAddress();
int getServerPort();
int getMaxSimultaneousConnection();
int getMaxPlayerPerRoom();
char *getExportFolderPath();

#endif /* PARSER_H */