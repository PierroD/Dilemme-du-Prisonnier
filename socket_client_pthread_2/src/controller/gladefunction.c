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

typedef struct
{

	int codeChoix;
	int codeMise;

} answer;

answer test;

int timer_id = 0;
int elapsed_time = 30;

int timer_handler()
{
	elapsed_time--;
	char txt[100];
	GtkLabel *timelabel = GTK_LABEL(gtk_builder_get_object(builder, "time_display"));
	snprintf(txt, 100, "%04i", elapsed_time);
	gtk_label_set_text(timelabel, txt);
	return 1;
}

// void on_progress() //barre de progression
// {

// 	g_print("%s", "je progresse");

// 	int timer = 300;
// 	char txt[100];

// 	for (int i = 0; i <= timer; i++)
// 	{

// 		GtkProgressBar *progressBar = gtk_builder_get_object(builder, "progressBar");
// 		gtk_progress_bar_set_fraction(progressBar, (double)i / timer); //valeurs entre 0 et 1 --- + cast

// 		GtkLabel *timelabel = GTK_LABEL(gtk_builder_get_object(builder, "time_display"));
// 		snprintf(txt, 100, "%03i", abs(i - timer));
// 		gtk_label_set_text(timelabel, txt);

// 		while (gtk_events_pending())
// 		{
// 			gtk_main_iteration();
// 		}

// 		delay(100);
// 	}

// 	gtk_main_quit();
// 	g_print("%s", "je ferme la fenetre");
// }

// void delay(unsigned int msecs)
// {
// 	clock_t goal = msecs * CLOCKS_PER_SEC / 1000 + clock();
// 	while (goal > clock())
// 	{
// 	};
// }

// void on_button_click() {
//     printf("bouton 'Yes' clicked\n");
//     GtkEntry *texte = GTK_ENTRY(gtk_builder_get_object(builder, "texte"));
//     gchar *data = (gchar *) gtk_entry_get_text(texte);
//     GtkEntry *echo = GTK_ENTRY(gtk_builder_get_object(builder, "echo"));
//     gtk_entry_set_text(echo, data);
// }

int on_click_1(GtkButton *button, GtkLabel *label) //Choix de la mise
{
	gtk_label_set_text(label, "1 ans");
	test.codeMise = 1;
}

int on_click_2(GtkButton *button, GtkLabel *label) //Choix de la mise
{
	gtk_label_set_text(label, "2 ans");
	test.codeMise = 2;
}

int on_click_5(GtkButton *button, GtkLabel *label) //Choix de la mise
{
	gtk_label_set_text(label, "5 ans");
	test.codeMise = 5;
}

int on_click_10(GtkButton *button, GtkLabel *label) //Choix de la mise
{
	gtk_label_set_text(label, "10 ans");
	test.codeMise = 10;
}

int on_click_50(GtkButton *button, GtkLabel *label) //Choix de la mise
{
	gtk_label_set_text(label, "50 ans");
	test.codeMise = 50;
}

int on_click_C(GtkButton *button, GtkLabel *label) //bouton collaborer
{ 

	gtk_label_set_text(label, "Collaborer");
	test.codeChoix = 0;
}

int on_click_T(GtkButton *button, GtkLabel *label) //bouton trahir
{ 

	gtk_label_set_text(label, "Trahir");
	test.codeChoix = 1;
}

void valide_answer(GtkButton *button, GtkLabel *label) //bouton envoyer
{ 

	gtk_label_set_text(label, "> ... En attente de l'autre joueur ... <");

	char code[5];
	switch (test.codeChoix)
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
	g_source_remove(timer_id);
	initwindowresults();
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
	builder = gtk_builder_new_from_file("src/view/newInterfaceResults.glade");
	win = GTK_WIDGET(gtk_builder_get_object(builder, "app_win_rst"));
	gtk_builder_connect_signals(builder, NULL);
	gtk_widget_show(win);
	gtk_main();
}