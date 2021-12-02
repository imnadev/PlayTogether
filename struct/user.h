#ifndef PLAYTOGETHER_USER_H
#define PLAYTOGETHER_USER_H

#include <stdbool.h>

typedef struct User User;

struct User {
    int id;

    char *name;
    int name_length;

    char *password;
    int password_length;

    char *address;
    int address_length;

    int server_id;
};

#endif
