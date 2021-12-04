#include <stdio.h>
#include <stdlib.h>
#include "vlc.h"

void vlc_init() {
    system("vlc -I rc --rc-host=localhost:9876");
}

void vlc_action(char * action) {
    printf("VLC: %s", action);
}