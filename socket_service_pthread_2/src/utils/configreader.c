#include <stdlib.h>
#include <libconfig.h>
#include "configreader.h"

void parse_game_configuration(Game *game_configuration, config_setting_t *setting)
{
    game_configuration->nb_room = config_setting_length(setting);
    game_configuration->rooms = malloc((int)game_configuration->nb_room * sizeof(Room));
    Room *current_room = game_configuration->rooms;
    for (int i = 0; i < game_configuration->nb_room; ++i)
    {
        config_setting_t *current_room_config = config_setting_get_elem(setting, i);
        config_setting_lookup_string(current_room_config, "name", &current_room->name);
        #if DEBUG
		printf("room name : %s\n", current_room->name);
		#endif
        config_setting_t *clients_room_config = config_setting_get_member(current_room_config, "clients");
        current_room->clients_name = (char **)malloc((int)2 * sizeof(char *));
        for (int j = 0; j < config_setting_length(clients_room_config); j++)
        {
        	current_room->clients_name[j] = (char *)malloc(100 * sizeof(char));
            config_setting_t *client_name_config = config_setting_get_elem(clients_room_config, j);
            config_setting_lookup_string(client_name_config, "name", &current_room->clients_name[j]);
            #if DEBUG
				printf("client name : %s\n", current_room->clients_name[j]);
			#endif
			
        }
        game_configuration->rooms[i] = *current_room;
        current_room++;
    }
}


void* read_configuration(Config *configuration, char *filename) {
	config_t config;
	config_setting_t *setting;
	config_init(&config);
	configuration = malloc(sizeof(Config));

	if (config_read_file(&config, filename)) {
		setting = config_lookup(&config, "games");
		Game *game = malloc(sizeof(Game));
		parse_game_configuration(&game, setting);
		configuration->game_config = game;
	} else {
		fprintf(stderr, "%s:%d - %s\n", config_error_file(&config),
				config_error_line(&config), config_error_text(&config));
		config_destroy(&config);
	}
}
