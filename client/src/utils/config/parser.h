#ifndef PARSER_H
#define PARSER_H

typedef struct
{
    char *server_ip_address;
    int server_port;
    char *view_file_path
} Config;

void parseConfig(char *filename);
Config getConfig();
char *getServerIpAddress();
int getServerPort();
char *getViewFilePath();

#endif /* PARSER_H */