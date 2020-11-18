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

#include "clientcxnmanager.h"

#include <gtk/gtk.h>

GtkBuilder *builder = NULL;


void on_progress(GtkButton *button){

	g_print("%s", "je progresse");

	int timer = 30;
	char txt[100]; 

	
	for (int i = 0; i <= timer; i++){

		GtkProgressBar * progressBar = gtk_builder_get_object(builder, "progressBar");
		gtk_progress_bar_set_fraction(progressBar, (double)i/timer );//valeurs entre 0 et 1 --- + cast

		GtkLabel *timelabel = GTK_LABEL(gtk_builder_get_object(builder, "time_display"));
		snprintf(txt, 100, "%03i", i);
    	gtk_label_set_text(timelabel, txt);

		while (gtk_events_pending()){
			gtk_main_iteration();
		}

		delay(1000);

		

	}

}

 

// void on_button_click() {
//     printf("bouton 'Yes' clicked\n");
//     GtkEntry *texte = GTK_ENTRY(gtk_builder_get_object(builder, "texte"));
//     gchar *data = (gchar *) gtk_entry_get_text(texte);
//     GtkEntry *echo = GTK_ENTRY(gtk_builder_get_object(builder, "echo"));
//     gtk_entry_set_text(echo, data);
// }

void on_click_C(GtkButton *button, GtkLabel *label) {

	gtk_label_set_text(label, "Collaborer");
	send_answer(1);
	
}

void on_click_T(GtkButton *button, GtkLabel *label) {

	gtk_label_set_text(label, "Trahir");
	send_answer(2);
	
}

void delay(unsigned int msecs){
    clock_t goal = msecs * CLOCKS_PER_SEC / 1000 + clock();
    while (goal > clock()){

	};
}

void valide_answer(GtkButton *button, GtkLabel *label) {
	gtk_label_set_text(label, "> ... En attente de l'autre joueur ... <");
	
}

void send_answer(int answer) {

	switch (answer)
	{
	case 1:
		//Un jour peut etre
		break;
	case 2:
		//Un jour peut etre
		break;
	
	default: 
		return -1;
		break;
	}
	
}

void on_cancel() {
    GtkWidget *message_dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL,
            GTK_MESSAGE_WARNING,
            GTK_BUTTONS_OK_CANCEL,
            "This action will cause the universe to stop existing.");
    //cf : http://refspecs.linuxbase.org/gtk/2.6/gtk/GtkMessageDialog.html
    //https://developer.gnome.org/gnome-devel-demos/stable/messagedialog.c.html.en
    unsigned int pressed = gtk_dialog_run(GTK_DIALOG(message_dialog));
    if (pressed == GTK_RESPONSE_OK) {
        printf("OK Pressed \n");
        printf("quitting\n ");
        gtk_widget_destroy(message_dialog);
        gtk_main_quit();
    } else {
        printf("CANCEL Pressed \n");
        gtk_widget_destroy(message_dialog);
    }
}

void on_window_main_destroy() {
    printf("quitting\n ");
    gtk_main_quit();
}

int main(int argc, char **argv) {

	GtkWidget *win;

    gtk_init(&argc, &argv);
    builder = gtk_builder_new_from_file("glade/newInterface.glade");
    win = GTK_WIDGET(gtk_builder_get_object(builder, "app_win"));
    gtk_builder_connect_signals(builder, NULL);
    gtk_widget_show(win);
    gtk_main();
    return (EXIT_SUCCESS);



	int sockfd;
	int status = 0;
	char msg[100];
	pthread_t thread;

	sockfd = open_connection();

	strcpy(msg, "Hello from Xeon"); //Xeon is the name of the this client
	printf("sending : %s\n", msg);
	write(sockfd, msg, strlen(msg));

	//Creation d'un pthread de lecture
	pthread_create(&thread, 0, threadProcess, &sockfd);
	//write(connection->sock,"Main APP Still running",15);
	pthread_detach(thread);
	do {
		fgets(msg, 100, stdin);
		//printf("sending : %s\n", msg);
		status = write(sockfd, msg, strlen(msg));
		//memset(msg,'\0',100);
	} while (status != -1);

	return (EXIT_SUCCESS);
}

