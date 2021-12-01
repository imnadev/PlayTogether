#ifndef PLAYTOGETHER_STRUCTS_H
#define PLAYTOGETHER_STRUCTS_H

#include <stdbool.h>

typedef struct User User;

struct User {
    int id;
    char name[50];
    char password[50];
    char ip[15];
    int port;
    bool approved;
};

#endif
