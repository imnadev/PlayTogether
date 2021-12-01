#ifndef PLAYTOGETHER_VLC_H
#define PLAYTOGETHER_VLC_H

#include <stdbool.h>

void vlc_is_available(void (*vlc_is_available_callback(bool))); // Check if vlc is available and send result to callback

void vlc_is_open(void (*vlc_is_open_callback(bool))); // Check if vlc is open and send result to callback

void vlc_play();

void vlc_pause();

void vlc_seek_forward(); //Seek 10 seconds forward

void vlc_seek_backward(); //Seek 10 seconds backward

void vlc_get_seek_position(void (*vlc_get_seek_position_callback(int))); //Get current video position in seconds

void vlc_set_seek_position(int); //Set current video position to given seconds

#endif
