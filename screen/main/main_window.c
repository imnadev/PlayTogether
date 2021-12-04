#include "main_window.h"
#include <gtk/gtk.h>
#include "../../socket/server/server.h"
#include "../../vlc/vlc.h"

GtkWidget *main_window;

void main_window_show(int type) {
    GtkBuilder *builder = gtk_builder_new_from_file("../screen/main/main_window.glade");
    main_window = GTK_WIDGET(gtk_builder_get_object(builder, "main_window"));
    gtk_builder_connect_signals(builder, NULL);

    g_object_unref(builder);
    gtk_widget_show(main_window);
}

void main_window_on_play_clicked() {
    vlc_action(PLAY);
    server_action(PLAY);
}