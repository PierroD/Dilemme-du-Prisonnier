#ifndef CONFIGREADER_H
#define CONFIGREADER_H

typedef struct
{
    char *server_ip_address;
    int server_port;
} Config;

void parseConfig(char *filename);
Config getConfig();
char *getServerIpAddress();
int getServerPort();

#endif /* CONFIGREADER_H */