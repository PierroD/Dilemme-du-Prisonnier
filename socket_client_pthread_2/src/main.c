/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: aurelio
 *
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

#include "./controller/connectionWindowController.h"
#include "./controller/gladefunction.h"
#include "clientcxnmanager.h"


void sendMessageToServices(char sendCode[5])
{

	int sockfd;
	char msg[5];
	strcpy(msg, sendCode);
	pthread_t thread;

	sockfd = open_connection();

	//Creation d'un pthread de lecture
	pthread_create(&thread, 0, threadProcess, &sockfd);
	//write(connection->sock,"Main APP Still running",15);
	pthread_detach(thread);

	write(sockfd, msg, strlen(msg));


	// do {
	// 	fgets(msg, 100, stdin);
	// 	//printf("sending : %s\n", msg);
	// 	status = write(sockfd, msg, strlen(msg));
	// 	//memset(msg,'\0',100);
	// } while (status != -1);
}

int main(int argc, char **argv)
{

	//initwindow(argc, argv);
	initConnectionWindow(argc, argv);
	return (EXIT_SUCCESS);
}
