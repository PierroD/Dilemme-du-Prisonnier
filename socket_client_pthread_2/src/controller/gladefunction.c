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

#include "gladefunction.h"

GtkBuilder *builder = NULL;
GtkBuilder *builderResults = NULL;

typedef enum {
	SILENT,
	BETRAY
}Choice;

typedef struct
{
	Choice codeChoix;
	int codeMise;

} answer;

Choice choice;
answer test;

int timer_id = 0;
int elapsed_time = 30;

int timer_handler()
{
	if(elapsed_time>0)
	{
	elapsed_time--;
	char txt[100];
	GtkLabel *timelabel = GTK_LABEL(gtk_builder_get_object(builder, "time_display"));
	GSList *builder_list = gtk_builder_get_objects(builder);
	builder_list;
	snprintf(txt, 100, "%04i", elapsed_time);
	gtk_label_set_text(timelabel, txt);
	return 1;
	}
}


int on_click_1(GtkButton *button, GtkLabel *label) //Choix de la mise
{
	gtk_label_set_text(label, "1 an");
	test.codeMise = 1;
}

int on_click_punishement(GtkButton *button, GtkLabel *label) //Choix de la mise
{
	gtk_label_set_text(label, gtk_button_get_label(button));
	char* text = gtk_button_get_label(button);
	text[strlen(text)-4] = 0;
	test.codeMise = atoi(text);
	strncat(text, " ans", 4);
	printf("valeur de la mise : %d \n",test.codeMise);
	gtk_button_set_label(button, text);
}

int on_click_C(GtkButton *button, GtkLabel *label) //bouton collaborer
{ 
	gtk_label_set_text(label, "Collaborer");
	test.codeChoix = SILENT;
}

int on_click_T(GtkButton *button, GtkLabel *label) //bouton trahir
{ 
	gtk_label_set_text(label, "Trahir");
	test.codeChoix = BETRAY;
}

int refresh_button(GtkButton *button, GtkLabel *label)
{
	int serviceAnswer = NULL;
	if(serviceAnswer != NULL)
	{

	}else
	{
		gtk_label_set_text(label, "> ... En attente de l'autre joueur ... <");
	}
	
}


void valide_answer() //bouton envoyer
{ 
	on_window_main_destroy();
	//initwindowresults();

	char code[5];
	switch (test.codeChoix)
	{
	case SILENT: //Collaborer
		code[0] = "0";
		sendMessageToServices(code);
		break;
	case 1: //Trahir
		code[0] = "1";
		sendMessageToServices(code);
		break;

	default:
		printf("%s", "ErrorSendingMessage \n");
		gtk_main_quit();
		break;
	}
	g_source_remove(timer_id);
	
}

void on_cancel() //boutton exit
{ 
	GtkWidget *message_dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_WARNING, 
	GTK_BUTTONS_OK_CANCEL, "This action will cause the universe to stop existing.");
	unsigned int pressed = gtk_dialog_run(GTK_DIALOG(message_dialog));
	if (pressed == GTK_RESPONSE_OK)
	{
		printf("OK Pressed \n");
		printf("quitting\n ");
		gtk_widget_destroy(message_dialog);
		gtk_main_quit();
	}
	else
	{
		printf("CANCEL Pressed \n");
		gtk_widget_destroy(message_dialog);
	}
}

void on_window_main_destroy()
{
	printf("quitting\n ");
	gtk_main_quit();
}

void initwindow() //newInterface.glade
{
	GtkWidget *win;
	gtk_init(0, NULL);
	builder = gtk_builder_new_from_file("src/view/newInterface.glade");
	win = GTK_WIDGET(gtk_builder_get_object(builder, "app_win"));
	gtk_builder_connect_signals(builder, NULL);
	gtk_widget_show(win);
	timer_id = g_timeout_add(1000, (GSourceFunc)timer_handler, NULL);
	gtk_main();
}

void initwindowresults() //newInterfaceResults.glade
{
	GtkWidget *win;
	gtk_init(0, NULL);
	builderResults = gtk_builder_new_from_file("src/view/newInterfaceResults.glade");
	win = GTK_WIDGET(gtk_builder_get_object(builderResults, "app_win_rst"));
	gtk_builder_connect_signals(builderResults, NULL);
	gtk_widget_show(win);
	gtk_main();
}