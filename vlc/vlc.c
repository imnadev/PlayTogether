#include <stdio.h>
#include <stdlib.h>
#include "vlc.h"

void vlc_init() {
    system("vlc -I rc --rc-host=localhost:9876");
}

void vlc_action(char * action) {
    printf("VLC: %s", action);
}

void vlc_set_seek_position(int position) {
    printf("VLC: SET_SEEK %d", position);
}

void vlc_stop() {

}