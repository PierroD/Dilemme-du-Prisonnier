/**
 * \file        parser.c
 * \brief       Recuperation de la configuration du serveur
 * */


#include <string.h>
#include "ini.h"
#include "parser.h"

Config config;



/**
 * Transforme une chaine de caractere en boolean
 *
 * @param input chaine de caractere
 * 
 * @return boolean
 * 
 * */


bool StringToBool(char *input)
{
    return (strcmp(input, "true") == 0) ? true : false;
}

/**
 * Recuperation de la configuration 
 *
 * @param filename nom du fichier de configuration
 * 
 * */

void ParseConfig(char *filename)
{
    ini_t *ini = ini_load(filename);
    config.server_ip_address = ini_get(ini, "network", "server_ip_address");
    config.server_port = atoi(ini_get(ini, "network", "server_port"));
    config.max_simultaneous_connection = atoi(ini_get(ini, "parameters", "max_simultaneous_connection"));
    config.max_player_per_room = atoi(ini_get(ini, "parameters", "max_player_per_room"));
    config.round_number = atoi(ini_get(ini, "parameters", "round_number"));
    config.time_to_decide = atoi(ini_get(ini, "parameters", "time_to_decide"));
    config.export_folder_path = ini_get(ini, "export", "export_folder_path");
    config.show_packet = StringToBool(ini_get(ini, "debug", "show_packet"));
    config.show_player = StringToBool(ini_get(ini, "debug", "show_player"));
    config.show_room = StringToBool(ini_get(ini, "debug", "show_room"));
    config.show_game = StringToBool(ini_get(ini, "debug", "show_game"));
    config.show_round = StringToBool(ini_get(ini, "debug", "show_round"));
    config.show_dilemma = StringToBool(ini_get(ini, "debug", "show_dilemma"));
    config.show_answer = StringToBool(ini_get(ini, "debug", "show_answer"));
    config.show_offset = StringToBool(ini_get(ini, "debug", "show_offset"));

}

/**
 * @return retourne la configuration
 * 
 * */

Config getConfig()
{
    return config;
}

/**
 * @return retourne l'adresse ip du serveur
 * 
 * */

char *getServerIpAddress()
{
    return config.server_ip_address;
}

/**
 * @return retourne le port du serveur
 * 
 * */

int getServerPort()
{
    return config.server_port;
}

/**
 * @return  retourne le nombre de connexion simultanées autorisés
 * 
 * */

int getMaxSimultaneousConnection()
{
    return config.max_simultaneous_connection;
}

/**
 * @return  retourne le nombre de joueur maximum autorisé par salle d'attente
 *
 * */

int getMaxPlayerPerRoom()
{
    return config.max_player_per_room;
}

/**
 * @return  retourne le chemin du dossier dans lequel les resultats seront stockes
 * 
 * */

char *getExportFolderPath()
{
    return config.export_folder_path;
}

/**
 * @return  Le nombre de round
 * 
 * */
int getRoundNumber()
{
    return config.round_number;
}

/**
 * @return  Le temps que le joueur a pour faire un choix
 * 
 * */
int getTimeToDecide()
{
    return config.time_to_decide;
}

///
/// ... Pour le debuguage ...
///


/**
 * @return  Le serveur doit affiché les packets
 * 
 * */

bool getShowPacket()
{
    return config.show_packet;
}

/**
 * @return  Le serveur doit affiché le joueur
 * 
 * */

bool getShowPlayer()
{
    return config.show_player;
}

/**
 * @return  Le serveur doit affiché la salle d'attente
 * 
 * */

bool getShowRoom()
{
    return config.show_room;
}

/**
 * @return  Le serveur doit affiché la partie
 * 
 * */

bool getShowGame()
{
    return config.show_game;
}

/**
 * @return  Le serveur doit affiché le round
 * 
 * */

bool getShowRound()
{
    return config.show_round;
}

/**
 * @return  Le serveur doit affiché le dilemme 
 * 
 * */

bool getShowDilemma()
{
    return config.show_dilemma;
}

/**
 * @return  Le serveur doit affiché la reponse
 * 
 * */

bool getShowAnswer()
{
    return config.show_answer;
}

/**
 * @return  Le serveur doit affiché les cellules memoires ou sont stockés les valeurs
 * 
 * */

bool getShowOffset()
{
    return config.show_offset;
}
