#include <string.h>
#include "ini.h"
#include "parser.h"

Config config;

bool StringToBool(char *input)
{
    return (strcmp(input, "true") == 0) ? true : false;
}

void ParseConfig(char *filename)
{
    ini_t *ini = ini_load(filename);
    config.server_ip_address = ini_get(ini, "network", "server_ip_address");
    config.server_port = atoi(ini_get(ini, "network", "server_port"));
    config.max_simultaneous_connection = atoi(ini_get(ini, "parameters", "max_simultaneous_connection"));
    config.max_player_per_room = atoi(ini_get(ini, "parameters", "max_player_per_room"));
    config.export_folder_path = ini_get(ini, "export", "export_folder_path");
    config.show_packet = StringToBool(ini_get(ini, "debug", "show_packet"));
    config.show_player = StringToBool(ini_get(ini, "debug", "show_player"));
    config.show_room = StringToBool(ini_get(ini, "debug", "show_room"));
    config.show_game = StringToBool(ini_get(ini, "debug", "show_game"));
    config.show_round = StringToBool(ini_get(ini, "debug", "show_round"));
    config.show_dilemma = StringToBool(ini_get(ini, "debug", "show_dilemma"));
    config.show_answer = StringToBool(ini_get(ini, "debug", "show_answer"));
    config.show_offset = StringToBool(ini_get(ini, "debug", "show_offset"));
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

char *getExportFolderPath()
{
    return config.export_folder_path;
}

bool getShowPacket()
{
    return config.show_packet;
}

bool getShowPlayer()
{
    return config.show_player;
}

bool getShowRoom()
{
    return config.show_room;
}

bool getShowGame()
{
    return config.show_game;
}

bool getShowRound()
{
    return config.show_round;
}

bool getShowDilemma()
{
    return config.show_dilemma;
}

bool getShowAnswer()
{
    return config.show_answer;
}

bool getShowOffset()
{
    return config.show_offset;
}
