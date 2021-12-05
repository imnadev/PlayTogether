#include "setup_window.h"
#include <gtk/gtk.h>
#include "../../socket/server/server.h"
#include "../main/main_window.h"
#include "../../socket/client/client.h"
#include "../../vlc/vlc.h"
#include <pthread.h>

GtkWidget *setup_window;
GtkWidget *entryAddress;
GtkWidget *entryPort;
char ip[16];
int port = 8877;

void setup_window_show() {
    GtkBuilder *builder = gtk_builder_new_from_file("../screen/setup/setup_window.glade");
    setup_window = GTK_WIDGET(gtk_builder_get_object(builder, "setup_window"));
    entryAddress = GTK_WIDGET(gtk_builder_get_object(builder, "entryAddress"));
    entryPort = GTK_WIDGET(gtk_builder_get_object(builder, "entryPort"));
    gtk_builder_connect_signals(builder, NULL);

    g_object_unref(builder);
    gtk_widget_show(setup_window);

    gtk_main();
}

void setup_window_on_serve_clicked() {
    vlc_connect();
    if (server_init() == FAILURE) {
        //TODO show error main_window
        gtk_main_quit();
    } else {
        gtk_widget_hide(setup_window);
        main_window_show(SERVER_WINDOW);
    }
}

void setup_window_on_connect_clicked() {
    vlc_connect();
    if (client_init(ip, port) == FAILURE) {
        //TODO show error main_window
        gtk_main_quit();
    } else {
        gtk_widget_hide(setup_window);
        main_window_show(CLIENT_WINDOW);
    }
}

void get_text(GtkEntry *e) {
    sprintf(ip, gtk_entry_get_text(e));
}

void get_port(GtkEntry *e) {
    char portChar[6];
    sprintf(portChar, gtk_entry_get_text(e));
    port = atoi(portChar);
}

void on_window_setup_destroy() {
    gtk_main_quit();
}
