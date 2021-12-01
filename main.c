#include <gtk/gtk.h>
#include "setup_window.h"

int main(int argc, char *argv[]) {

    gtk_init(&argc, &argv);

    show_setup_window();

    return 0;
}
