#include "connectionWindowController.h"

GtkBuilder *bld_ConnectionWindow = NULL;
GtkWidget *widgets;

void btn_ready_click(GtkButton *button, GtkLabel *label)
{
    write_buffer(serializeMessage(PLAYER_READY, "Player is ready"));
    setlblStatusText("En attente d'acceptation des autres joueurs");
}

void setButtonReadyToVisible()
{
    GtkWidget *btnReady = GTK_WIDGET(gtk_builder_get_object(bld_ConnectionWindow, "btn_ready"));
    setlblStatusText("Vous êtes connecté");
    gtk_widget_show(btnReady);
}

void show_gameWindows()
{
    initwindow();
}

void setlblStatusText(char *text)
{
    GtkLabel *lblStatus = GTK_LABEL(gtk_builder_get_object(bld_ConnectionWindow, "lbl_status"));
    gtk_label_set_text(lblStatus, text);
}

void initConnectionWindow()
{
    gtk_init(0, NULL);
    bld_ConnectionWindow = gtk_builder_new_from_file("src/view/ConnectionWindow.glade");
    widgets = GTK_WIDGET(gtk_builder_get_object(bld_ConnectionWindow, "connection_window"));
    gtk_builder_connect_signals(bld_ConnectionWindow, NULL);
    g_object_set(gtk_settings_get_default(),
                 "gtk-application-prefer-dark-theme", TRUE,
                 NULL);
    gtk_widget_show_all(widgets);
    gtk_main();
}