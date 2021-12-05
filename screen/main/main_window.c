#include "main_window.h"
#include <gtk/gtk.h>
#include "../../socket/server/server.h"
#include "../../vlc/vlc.h"
#include "../setup/setup_window.h"
#include "../../socket/client/client.h"

GtkWidget *main_window;
int window_type;

void main_window_show(int type) {

    window_type = type;

    GtkBuilder *builder = gtk_builder_new_from_file("../screen/main/main_window.glade");

    if (type == SERVER_WINDOW) {
        main_window = GTK_WIDGET(gtk_builder_get_object(builder, "server_window"));
    } else {
        main_window = GTK_WIDGET(gtk_builder_get_object(builder, "client_window"));
    }
    gtk_builder_connect_signals(builder, NULL);

    g_object_unref(builder);
    gtk_widget_show(main_window);
}

void main_window_on_play_clicked() {
    vlc_action(PLAY);
    server_action(PLAY);
}

void main_window_on_sync_clicked() {
    if (window_type == SERVER_WINDOW) {
        server_action(SYNC);
    } else {
        client_sync();
    }
}

void main_window_on_pause_clicked() {
    vlc_action(PAUSE);
    server_action(PAUSE);
}

void main_window_on_seek_backward_clicked() {
    vlc_action(SEEK_BACKWARD);
    server_action(SEEK_BACKWARD);
}

void main_window_on_seek_forward_clicked() {
    vlc_action(SEEK_FORWARD);
    server_action(SEEK_FORWARD);
}

void main_window_on_exit_clicked() {
    server_stop();
    client_stop();
    vlc_stop();
    gtk_widget_hide(main_window);
    setup_window_show();
}

void on_window_main_destroy() {
    server_stop();
    client_stop();
    vlc_stop();
    gtk_main_quit();
}