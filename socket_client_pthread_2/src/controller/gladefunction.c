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
#include "../includes/packet.h"
#include "../utils/bufferreader.h"

GtkBuilder *builder = NULL;


Answer *answer;

int timer_id = 0;
int elapsed_time = 30;

int timer_handler()
{
	if (elapsed_time > 0)
	{
		elapsed_time--;
		char txt[100];
		GtkLabel *timelabel = GTK_LABEL(gtk_builder_get_object(builder, "time_display"));
		snprintf(txt, 100, "%04i", elapsed_time);
		gtk_label_set_text(timelabel, txt);
		return 1;
	}
}

int btn_1y_click(GtkButton *button, GtkLabel *label) //Choix de la mise
{
	gtk_label_set_text(label, "1 an");
	answer->bet = 1;
}

int btn_punishement_click(GtkButton *button, GtkLabel *label) //Choix de la mise
{
	gtk_label_set_text(label, gtk_button_get_label(button));
	char *text = gtk_button_get_label(button);
	text[strlen(text) - 4] = 0;
	answer->bet = atoi(text);
	strncat(text, " ans", 4);
	printf("valeur de la mise : %d \n", answer->bet);
	gtk_button_set_label(button, text);
}

int btn_silent_click(GtkButton *button, GtkLabel *label) //bouton collaborer
{
	gtk_label_set_text(label, "Collaborer");
	answer->choice = SILENT;
}

int btn_betray_click(GtkButton *button, GtkLabel *label) //bouton trahir
{
	gtk_label_set_text(label, "Trahir");
	answer->choice = BETRAY;
}


void valide_answer() //bouton envoyer
{
	on_window_main_destroy();
	//initwindowresults();
	write_buffer(serializeData(RESPONSE, answer, sizeof(Answer)));
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
	answer = (Answer *)malloc(sizeof(Answer));
	g_object_set(gtk_settings_get_default(),
				 "gtk-application-prefer-dark-theme", TRUE,
				 NULL);
	gtk_widget_show(win);
	timer_id = g_timeout_add(1000, (GSourceFunc)timer_handler, NULL);
	gtk_main();
}

