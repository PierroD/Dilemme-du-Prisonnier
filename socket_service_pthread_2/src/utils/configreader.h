#ifndef CONFIGREADER_HEADER_FILE_H
#define CONFIGREADER_HEADER_FILE_H
typedef struct{
    char *name;
    char **clients_name;
} Room;

typedef struct
{
    int *nb_room;
    Room *rooms;
} Game;

typedef struct
{
    Game *game_config;
} Config;


void *read_configuration(Config *configuration, char *filename);
#endif
