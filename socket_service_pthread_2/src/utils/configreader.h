#ifndef CONFIGREADER_H
#define CONFIGREADER_H

typedef struct {
    char *server_ip_address;
    int server_port;
    int max_simultaneous_connection;
} Config;


Config parseConfig(char *filename);
Config getConfig();
char *getServerIpAddress();
int getServerPort();
int getMaxSimultaneousConnection();

#endif /* CONFIGREADER_H */