#ifndef PLAYTOGETHER_CLIENT_H
#define PLAYTOGETHER_CLIENT_H

#include "../../struct/user.h"

void client_init(
        char *ip,
        char *port
);

void client_get_users(void (*set_users(User *)));

void client_sync();

#endif
