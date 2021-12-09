Installing VLC
> sudo dnf install https://download1.rpmfusion.org/free/fedora/rpmfusion-free-release-$(rpm -E %fedora).noarch.rpm

> sudo dnf install https://download1.rpmfusion.org/nonfree/fedora/rpmfusion-nonfree-release-$(rpm -E %fedora).noarch.rpm

> sudo dnf install gtk3-devel vlc telnet

> vlc -I rc --rc-host=localhost:9988

Running VLC
> telnet localhost 9988

> enqueue /path/to/video.mp4

Installing and running PlayTogether
> git clone https://github.com/imnadev/PlayTogether.git

> cd main

> gcc -export-dynamic -Wall main.c ../database/database.c ../screen/main/main_window.c ../screen/setup/setup_window.c ../socket/client/client.c ../socket/server/server.c ../vlc/vlc.c -o PlayTogether -pthread \`pkg-config --cflags --libs gtk+-3.0\` && ./PlayTogether