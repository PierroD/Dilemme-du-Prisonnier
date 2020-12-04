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


int timer_handler();
/*Buttons click event*/
int btn_1y_click(GtkButton *button, GtkLabel *label);
int btn_punishement_click(GtkButton *button, GtkLabel *label);
int btn_silent_click(GtkButton *button, GtkLabel *label);
int btn_betray_click(GtkButton *button, GtkLabel *label);


void valide_answer();
void on_cancel();
void on_window_main_destroy();

/*Window initialization*/
void initwindow();

