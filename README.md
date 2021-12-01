**Installing requirements:**
   * On Fedora 
     > sudo dnf install gtk3-devel

**To build and run the project:**
> gcc -export-dynamic -Wall `pkg-config --cflags --libs gtk+-3.0` main.c client_window.c db.c server_window.c setup_window.c socket.c -o PlayTogether -pthread `pkg-config --cflags --libs gtk+-3.0` && ./PlayTogether
