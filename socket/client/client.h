#ifndef PLAYTOGETHER_CLIENT_H
#define PLAYTOGETHER_CLIENT_H

#include "../../struct/user.h"
#include "../../struct/constants.h"

int client_init(
        char *ip,
        int port
);

void client_get_users(void (*set_users(User *)));

void client_sync();

void client_stop();

#endif
