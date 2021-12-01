#ifndef PLAYTOGETHER_SERVER_H
#define PLAYTOGETHER_SERVER_H

#include "../../struct/user.h"

void server_init(
        void (*server_init_status_callback()),
        User *user
);

void server_get_users(void (*set_users(User *)));

void server_sync();

void server_play();

void server_pause();

void server_seek_forward();

void server_seek_backward();

#endif
