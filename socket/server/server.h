#ifndef PLAYTOGETHER_SERVER_H
#define PLAYTOGETHER_SERVER_H

#include "../../struct/user.h"
#include "../../struct/constants.h"

int server_init();

void server_get_users(void (*set_users(User *)));

void server_sync();

void server_action(char *action);   //PLAY, PAUSE, SEEK_FORWARD, SEEK_BACKWARD

void server_stop();

#endif
