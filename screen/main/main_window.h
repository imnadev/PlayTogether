#ifndef PLAYTOGETHER_CLIENT_WINDOW_H
#define PLAYTOGETHER_CLIENT_WINDOW_H


#define SERVER_WINDOW 0
#define CLIENT_WINDOW 1

/*
 * Called from setup_window with above SERVER_WINDOW and CLIENT_WINDOW values as type
 * Draws the main_window according to the type
 * Gets users list from server.h or client.h
 * Sets main_window text as 'Connected to'/'Serving at' 192.168.0.123:8080
 */
void main_window_show(int type);

/*
 * Called from glade on sync button clicked
 * Calls sync function on server.h or client.h
 */
void main_window_on_sync_clicked();

/*
 * Called from glade on play button clicked
 * Calls play function on server.h
 */
void main_window_on_play_clicked();

/*
 * Called from glade on pause button clicked
 * Calls pause function on server.h
 */
void main_window_on_pause_clicked();

/*
 * Called from glade on seek backward button clicked
 * Calls pause function on server.h
 */
void main_window_on_seek_backward_clicked();

/*
 * Called from glade on seek forward button clicked
 * Calls pause function on server.h
 */
void main_window_on_seek_forward_clicked();

/*
 * Called from glade on exit button clicked
 * Calls pause function on server.h
 */
void main_window_on_exit_clicked();

#endif
