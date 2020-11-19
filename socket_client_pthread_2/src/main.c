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

#include "clientcxnmanager.h"


GtkBuilder *builder = NULL;

typedef struct {

	int code;

}answer;

answer test;

void on_progress(GtkButton *button){ //bar de progression

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

void delay(unsigned int msecs){
    clock_t goal = msecs * CLOCKS_PER_SEC / 1000 + clock();
    while (goal > clock()){

	};
}

// void on_button_click() {
//     printf("bouton 'Yes' clicked\n");
//     GtkEntry *texte = GTK_ENTRY(gtk_builder_get_object(builder, "texte"));
//     gchar *data = (gchar *) gtk_entry_get_text(texte);
//     GtkEntry *echo = GTK_ENTRY(gtk_builder_get_object(builder, "echo"));
//     gtk_entry_set_text(echo, data);
// }

int on_click_C(GtkButton *button, GtkLabel *label) { //bouton collaborer

	gtk_label_set_text(label, "Collaborer");
	
	test.code = 0;
	
}

int on_click_T(GtkButton *button, GtkLabel *label) { //bouton trahir

	gtk_label_set_text(label, "Trahir");
	
	test.code = 1;	
	
}


void valide_answer(GtkButton *button, GtkLabel *label) { //bouton envoyer
	gtk_label_set_text(label, "> ... En attente de l'autre joueur ... <");
	
	char code[5];
	switch (test.code)
		{
			case 0: //Collaborer
				code[0] = "0";
				sendMessageToServices(code);
				break;
			case 1: //Trahir
				code[0] = "1";
				sendMessageToServices(code);
				break;
	
			default: 
				printf("%s", "ErrorMessage \n");
				gtk_main_quit();
				break;
	} 

}


void on_cancel() { // bouton exit
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

void sendMessageToServices(char sendCode[5]){

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


int main(int argc, char **argv) {

	GtkWidget *win;

    gtk_init(&argc, &argv);
    builder = gtk_builder_new_from_file("glade/newInterface.glade");
    win = GTK_WIDGET(gtk_builder_get_object(builder, "app_win"));
    gtk_builder_connect_signals(builder, NULL);
    gtk_widget_show(win);
	//on_progress(); // --> Lancement au demarage du timer
    gtk_main();
    return (EXIT_SUCCESS);


}

