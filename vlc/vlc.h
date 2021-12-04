#ifndef PLAYTOGETHER_VLC_H
#define PLAYTOGETHER_VLC_H

#include <stdbool.h>

void vlc_action(char * action); //PLAY, PAUSE, SEEK_FORWARD, SEEK_BACKWARD

int vlc_get_seek_position(); //Get current video position in seconds

void vlc_set_seek_position(int); //Set current video position to given seconds

#endif
