#ifndef PLAYTOGETHER_DATABASE_H
#define PLAYTOGETHER_DATABASE_H

#include "../struct/user.h"

void database_init();

void database_insert_user(User *user);

User* database_get_users(int server_id);

#endif