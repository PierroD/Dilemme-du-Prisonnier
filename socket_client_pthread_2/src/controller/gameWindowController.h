#ifndef GAMEWINDOWCONTROLLER_H
#define GAMEWINDOWCONTROLLER_H

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
#include "../utils/response.h"


/*Buttons click event*/
int btn_1y_click(GtkButton *button, GtkLabel *label);
int btn_punishement_click(GtkButton *button, GtkLabel *label);
int btn_silent_click(GtkButton *button, GtkLabel *label);
int btn_betray_click(GtkButton *button, GtkLabel *label);
void btn_ready_click(GtkButton *button, GtkLabel *label);
void btn_validate_click();
void btn_exit_click();

void on_window_main_destroy();

/*Window initialization*/
void initGameWindow();


/* Non GUI events*/
void setButtonReadyVisible(bool visibleState);
void setlblStatusText(char *text);
void newDilemma(int timeToDecide, int MaxPunishement);
void showHideGameWindow(bool showState);
void showOrHideChoices(bool showChoices);
int progessbar_timer();

#endif /* GAMEWINDOWCONTROLLER_H */