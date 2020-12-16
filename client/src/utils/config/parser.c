/**
 * \file        parser.c
 * \brief       ???
 * */


#include "parser.h"
#include "ini.h"

Config config;

void parseConfig(char *filename)
{
    ini_t *ini = ini_load(filename);
    config.server_ip_address = ini_get(ini, "network", "server_ip_address");
    config.server_port = atoi(ini_get(ini, "network", "server_port"));
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
