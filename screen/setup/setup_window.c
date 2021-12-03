#include "setup_window.h"
#include <gtk/gtk.h>
#include "../../socket/server/server.h"
#include <pthread.h>

void *start_server(void *) {

    User user;
    user.name = "m_username";
    user.password = "m_password";

    if (server_init(&user) == FAILURE) {
        gtk_main_quit();
    } else {
        puts("SUCCESS");
    }
}

void setup_window_show() {
    GtkBuilder *builder = gtk_builder_new_from_file("../screen/setup/setup_window.glade");
    GtkWidget *window = GTK_WIDGET(gtk_builder_get_object(builder, "setup_window"));
    gtk_builder_connect_signals(builder, NULL);

    g_object_unref(builder);
    gtk_widget_show(window);

    pthread_t my_thread;
    pthread_create(&my_thread, NULL, start_server, NULL);

    gtk_main();
}

void on_window_setup_destroy() {
    gtk_main_quit();
}

