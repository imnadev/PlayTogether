**Installing requirements:**
   * On Fedora 
     > sudo dnf install gtk3-devel

**To build and run the project:**
> gcc -export-dynamic -Wall `pkg-config --cflags --libs gtk+-3.0` main/main.c database/database.c screen/client/client_window.c screen/server/server_window.c screen/setup/setup_window.c socket/client/client_socket.c socket/server/server_socket.c vlc/vlc.c -o PlayTogether -pthread `pkg-config --cflags --libs gtk+-3.0` && ./PlayTogether