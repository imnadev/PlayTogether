#include <gtk/gtk.h>
#include "setup_window.h"
#include "db.h"
#include "socket.h"

int main(int argc, char *argv[]) {

    init_database();
    init_socket();

    gtk_init(&argc, &argv);

    show_setup_window();
    return 0;
}
