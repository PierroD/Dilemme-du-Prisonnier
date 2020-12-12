#ifndef PARSER_H
#define PARSER_H

typedef struct
{
    char *server_ip_address;
    int server_port;
} Config;

void parseConfig(char *filename);
Config getConfig();
char *getServerIpAddress();
int getServerPort();

#endif /* PARSER_H */