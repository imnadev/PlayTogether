#ifndef PLAYTOGETHER_DATABASE_H
#define PLAYTOGETHER_DATABASE_H

#include "../struct/user.h"
#include "../struct/constants.h"

int database_insert_user(User *user); //return SUCCESS or FAILURE

User* database_get_users(int server_id);

#endif