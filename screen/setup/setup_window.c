#include "setup_window.h"
#include <gtk/gtk.h>
#include "../../socket/server/server.h"
#include "../main/main_window.h"
#include "../../socket/client/client.h"
#include "../../vlc/vlc.h"
#include <pthread.h>

GtkWidget *setup_window;
GtkWidget *entry1;
GtkWidget *label1;

void setup_window_show() {
    GtkBuilder *builder = gtk_builder_new_from_file("../screen/setup/setup_window.glade");
    setup_window = GTK_WIDGET(gtk_builder_get_object(builder, "setup_window"));
    entry1 = GTK_WIDGET(gtk_builder_get_object(builder, "entry1"));
    label1 = GTK_WIDGET(gtk_builder_get_object(builder, "label1"));
    gtk_builder_connect_signals(builder, NULL);

    g_object_unref(builder);
    gtk_widget_show(setup_window);

    gtk_main();
}

void setup_window_on_serve_clicked() {
//    vlc_connect();
    if (server_init() == FAILURE) {
        //TODO show error main_window
        gtk_main_quit();
    } else {
        gtk_widget_hide(setup_window);
        main_window_show(SERVER_WINDOW);
    }
}

void setup_window_on_connect_clicked() {
//    vlc_connect();
    //TODO get ip and port from screen
    if (client_init("127.0.0.1", 8888) == FAILURE) {
        //TODO show error main_window
        gtk_main_quit();
    } else {
        gtk_widget_hide(setup_window);
        main_window_show(CLIENT_WINDOW);
    }
}

void get_text(GtkEntry *e){
	char tmp[16];
	sprintf(tmp, "entry:%s", gtk_entry_get_text(e));
	gtk_label_set_text(GTK_LABEL(label1), (const gchar*) tmp);
}

void on_window_setup_destroy() {
    gtk_main_quit();
}

