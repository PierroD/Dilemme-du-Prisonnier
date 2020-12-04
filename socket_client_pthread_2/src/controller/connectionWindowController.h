#ifndef CONNECTIONWINDOWCONTROLLER_H
#define CONNECTIONWINDOWCONTROLLER_H


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

#include "../utils/bufferreader.h"
#include "../utils/serialize.h"
#include "../includes/packet.h"
#include "gladefunction.h"

/*Buttons click event*/
void btn_ready_click(GtkButton *button, GtkLabel *label);

/*Window initialization*/
void initConnectionWindow();


/*Non GUI events*/
void setButtonReadyToVisible();

#endif /* CONNECTIONWINDOWCONTROLLER_H */