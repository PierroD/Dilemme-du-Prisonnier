/**
 * \file		client.c(main)
 * \author    	Pierre Hugo Harut Nassim
 * \version   	1.0
 * \date       	15 decembre 2020
 * \brief		Gestion et envoi des donnees clients
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <pthread.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdbool.h>
#include <time.h>
#include <gtk/gtk.h>

#include "./controller/gameWindowController.h"
#include "./utils/connection/manager.h"

int main(int argc, char **argv)
{
	initGameWindow();
	return (EXIT_SUCCESS);
}
