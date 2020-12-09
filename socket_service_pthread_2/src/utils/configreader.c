#include "ini.h"
#include "configreader.h"

Config config;

void parseConfig(char *filename)
{
    ini_t *ini = ini_load(filename);
    config.server_ip_address = ini_get(ini, "network", "server_ip_address");
    config.server_port = atoi(ini_get(ini, "network", "server_port"));
    config.max_simultaneous_connection = atoi(ini_get(ini, "network", "max_simultaneous_connection"));
    config.max_player_per_room = atoi(ini_get(ini, "network", "max_player_per_room"));
    return config;
}

Config getConfig()
{
    return config;
}

char *getServerIpAddress()
{
    return config.server_ip_address;
}

int getServerPort()
{
    return config.server_port;
}

int getMaxSimultaneousConnection()
{
    return config.max_simultaneous_connection;
}

int getMaxPlayerPerRoom()
{
    return config.max_player_per_room;
}