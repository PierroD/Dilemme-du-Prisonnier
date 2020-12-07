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

#include "gameWindowController.h"
#include "../includes/packet.h"
#include "../utils/bufferreader.h"

GtkBuilder *bld_GameWindow = NULL;
GtkWidget *gameWidgets;

Answer *answer;
bool hasBet, isChoice;

#pragma region Non GUI events
int timer_id = 0;
int elapsed_time = 30;
int pbar_max_value = 30;
int progessbar_timer()
{
	if (elapsed_time > 0)
	{
		elapsed_time--;
		//pbar
		gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(gtk_builder_get_object(bld_GameWindow, "pbar_timeLeft")), (gdouble)elapsed_time / pbar_max_value);
		// set lblEvent text
		char txt[100];
		snprintf(txt, 100, "%02i", elapsed_time);
		setLblEventsText(txt);
		return 1;
	}
}

void setLblEventsText(char *text)
{
	GtkLabel *timelabel = GTK_LABEL(gtk_builder_get_object(bld_GameWindow, "lbl_events"));
	gtk_label_set_text(timelabel, text);
}

void setButtonReadyVisible(bool visibleState)
{
	GtkWidget *btnReady = GTK_BUTTON(gtk_builder_get_object(bld_GameWindow, "btn_ready"));
	if (visibleState)
		gtk_widget_show(btnReady);
	else
		gtk_widget_hide(btnReady);
}

void setlblStatusText(char *text)
{
	GtkLabel *lblStatus = GTK_LABEL(gtk_builder_get_object(bld_GameWindow, "lbl_status"));
	gtk_label_set_text(lblStatus, text);
}

void setHasBet(bool betState)
{
	hasBet = betState;
}

void setIsChoice(bool choiceState)
{
	isChoice = choiceState;
}

void newDilemma(int timeToDecide, int MaxPunishement)
{
	elapsed_time = timeToDecide;
	pbar_max_value = timeToDecide;
	showOrHideChoices(true);
	timer_id = g_timeout_add(1000, (GSourceFunc)progessbar_timer, NULL);
}

void showOrHideChoices(bool showChoices)
{
	GtkWidget *btnSilent = GTK_WIDGET(gtk_builder_get_object(bld_GameWindow, "btn_silent"));
	GtkWidget *btnBetray = GTK_WIDGET(gtk_builder_get_object(bld_GameWindow, "btn_betray"));
	GtkWidget *btn_1 = GTK_WIDGET(gtk_builder_get_object(bld_GameWindow, "btn_1"));
	GtkWidget *btn_2 = GTK_WIDGET(gtk_builder_get_object(bld_GameWindow, "btn_2"));
	GtkWidget *btn_5 = GTK_WIDGET(gtk_builder_get_object(bld_GameWindow, "btn_5"));
	GtkWidget *btn_10 = GTK_WIDGET(gtk_builder_get_object(bld_GameWindow, "btn_10"));
	if (showChoices)
	{
		setIsChoice(false);
		setHasBet(false);
		gtk_widget_show(btnBetray);
		gtk_widget_show(btnSilent);
		gtk_widget_show(btn_1);
		gtk_widget_show(btn_2);
		gtk_widget_show(btn_5);
		gtk_widget_show(btn_10);
	}
	else
	{
		elapsed_time = 0;
		setLblEventsText("en attente des autres joueurs");
		gtk_widget_hide(btnBetray);
		gtk_widget_hide(btnSilent);
		gtk_widget_hide(btn_1);
		gtk_widget_hide(btn_2);
		gtk_widget_hide(btn_5);
		gtk_widget_hide(btn_10);
	}
}

void showHideGameWindow(bool showState)
{
	GtkWidget *box_game = GTK_BOX(gtk_builder_get_object(bld_GameWindow, "box_game"));
	GtkWidget *box_connection = GTK_BOX(gtk_builder_get_object(bld_GameWindow, "box_connection"));

	if (showState)
	{
		gtk_widget_show(box_game);
		gtk_widget_hide(box_connection);
	}
	else
	{
		gtk_widget_show(box_connection);
		gtk_widget_hide(box_game);
	}
}
#pragma endregion

#pragma region buttons click events
void btn_ready_click(GtkButton *button, GtkLabel *label)
{
	response_PlayerIsReady();
}

int btn_1y_click(GtkButton *button, GtkLabel *label) //Choix de la mise
{
	gtk_label_set_text(label, "1 an");
	setHasBet(true);
	answer->bet = 1;
}

int btn_punishement_click(GtkButton *button, GtkLabel *label) //Choix de la mise
{
	gtk_label_set_text(label, gtk_button_get_label(button));
	char *text = gtk_button_get_label(button);
	text[strlen(text) - 4] = 0;
	setHasBet(true);
	answer->bet = atoi(text);
	strncat(text, " ans", 4);
	gtk_button_set_label(button, text);
}

int btn_silent_click(GtkButton *button, GtkLabel *label) //bouton collaborer
{
	gtk_label_set_text(label, "Collaborer");
	setIsChoice(true);
	answer->choice = SILENT;
}

int btn_betray_click(GtkButton *button, GtkLabel *label) //bouton trahir
{
	gtk_label_set_text(label, "Trahir");
	setIsChoice(true);
	answer->choice = BETRAY;
}

void btn_validate_click() //bouton envoyer
{
	if (hasBet && isChoice)
	{
		answer->time_to_decide = pbar_max_value - elapsed_time;
		response_PlayerAnswer(answer);
		g_source_remove(timer_id);
		showOrHideChoices(false);
	}
}

void btn_exit_click() //boutton exit
{
	GtkWidget *message_dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_WARNING,
													   GTK_BUTTONS_OK_CANCEL, "This action will cause the universe to stop existing.");
	unsigned int pressed = gtk_dialog_run(GTK_DIALOG(message_dialog));
	if (pressed == GTK_RESPONSE_OK)
	{
		printf("OK Pressed \n");
		printf("quitting\n ");
		gtk_widget_destroy(message_dialog);
		//gtk_widget_destroy(parentWidgets);
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

#pragma endregion

#pragma region initialization window
void initGameWindow() //gameWindow.glade
{
	gtk_init(0, NULL);
	bld_GameWindow = gtk_builder_new_from_file("src/view/GameWindow.glade");
	gameWidgets = GTK_WIDGET(gtk_builder_get_object(bld_GameWindow, "game_window"));
	gtk_builder_connect_signals(bld_GameWindow, NULL);
	answer = (Answer *)malloc(sizeof(Answer));
	g_object_set(gtk_settings_get_default(),
				 "gtk-application-prefer-dark-theme", TRUE,
				 NULL);
	gtk_widget_show_all(gameWidgets);
	showHideGameWindow(false);
	openThread();
	gtk_main();
}
#pragma endregion