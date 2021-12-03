#ifndef PLAYTOGETHER_USER_H
#define PLAYTOGETHER_USER_H

#include <stdbool.h>

typedef struct User User;

struct User {
    int id;

    char *name;

    char *password;

    char *address;

    int server_id;
};

#endif
