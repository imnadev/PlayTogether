#ifndef PLAYTOGETHER_CLIENT_H
#define PLAYTOGETHER_CLIENT_H

#include "../../struct/user.h"

void client_init(
        void (*client_init_status_callback()),
        User *user,
        char address[21],
        int length
);

void client_get_users(void (*set_users(User *)));

void client_sync();

#endif
