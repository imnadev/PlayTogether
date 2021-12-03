#ifndef PLAYTOGETHER_SERVER_H
#define PLAYTOGETHER_SERVER_H

#include "../../struct/user.h"
#include "../../struct/constants.h"

int server_init(User *user);

void server_get_users(void (*set_users(User *)));

void server_sync();

void server_play();

void server_pause();

void server_seek_forward();

void server_seek_backward();

#endif
