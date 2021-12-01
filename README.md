**Installing requirements:**
   * On Fedora 
     > sudo dnf install gtk3-devel
   * On Ubuntu 
     > sudo apt-get install libgtk-3-dev

**To build and run the project just click Run on CLion or run the following command inside `main` directory:**
> gcc -export-dynamic -Wall `pkg-config --cflags --libs gtk+-3.0` main.c ../database/database.c ../screen/main/main_window.c ../screen/setup/setup_window.c ../socket/client/client.c ../socket/server/server.c ../vlc/vlc.c -o PlayTogether -pthread `pkg-config --cflags --libs gtk+-3.0` && ./PlayTogether

