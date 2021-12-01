#ifndef PLAYTOGETHER_DB_H
#define PLAYTOGETHER_DB_H

#include "structs.h"

void init_database();

void insert_user(User *user);

void get_users(void (*set_users(User *)));

#endif