
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
int on_click_1(GtkButton *button, GtkLabel *label);
int on_click_2(GtkButton *button, GtkLabel *label);
int on_click_5(GtkButton *button, GtkLabel *label);
int on_click_10(GtkButton *button, GtkLabel *label);
int on_click_50(GtkButton *button, GtkLabel *label);
//void on_progress();
//void time_counter();
//void delay(unsigned int msecs);
int on_click_C(GtkButton *button, GtkLabel *label);
int on_click_T(GtkButton *button, GtkLabel *label);
void valide_answer();
void on_cancel();
void on_window_main_destroy();
void initwindow();
void initwindowresults();
