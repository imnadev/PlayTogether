#include "setup_window.h"
#include <gtk/gtk.h>

void show_setup_window() {
    GtkBuilder *builder = gtk_builder_new_from_file("screen/setup/setup_window.glade");
    GtkWidget *window = GTK_WIDGET(gtk_builder_get_object(builder, "setup_window"));
    gtk_builder_connect_signals(builder, NULL);

    g_object_unref(builder);
    gtk_widget_show(window);
    gtk_main();
}

void on_window_setup_destroy() {
    gtk_main_quit();
}
