#include "setup_window.h"
#include <gtk/gtk.h>
#include "../../socket/server/server.h"
#include "../main/main_window.h"
#include <pthread.h>

GtkWidget *setup_window;

void setup_window_show() {
    GtkBuilder *builder = gtk_builder_new_from_file("../screen/setup/setup_window.glade");
    setup_window = GTK_WIDGET(gtk_builder_get_object(builder, "setup_window"));
    gtk_builder_connect_signals(builder, NULL);

    g_object_unref(builder);
    gtk_widget_show(setup_window);

    gtk_main();
}

void setup_window_on_serve_clicked() {
    if (server_init() == FAILURE) {
        //TODO show error main_window
        gtk_main_quit();
    } else {
        gtk_widget_hide(setup_window);
        main_window_show(SERVER_WINDOW);
    }
}

void on_window_setup_destroy() {
    gtk_main_quit();
}

