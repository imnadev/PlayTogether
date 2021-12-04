#ifndef PLAYTOGETHER_SETUP_WINDOW_H
#define PLAYTOGETHER_SETUP_WINDOW_H

/*
 * Called from main(), just opens the setup main_window.
 * Writes server ip and port number on screen
 */
void setup_window_show();

/*
 * Called from glade when serve button clicked.
 * Inits server.h with user details
 * Opens main_window as server on success
 */
void setup_window_on_serve_clicked();

/*
 * Called from glade when connect button clicked.
 * Inits client.h with server details
 * Sends user details to server
 * Opens main_window as client on success
 */
void setup_window_on_connect_clicked();

/*
 * Called from the same setup_window when any error occurs
 * Opens an error screen with specified message
 */
void setup_window_error(char* message, int length);

void server_init_status_callback(int status);

#endif
