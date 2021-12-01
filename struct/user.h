#ifndef PLAYTOGETHER_USER_H
#define PLAYTOGETHER_USER_H

#include <stdbool.h>

typedef struct User User;

struct User {
    int id;
    char name[50];
    char password[50];
    char address[21];
    int server_id;
};

#endif
