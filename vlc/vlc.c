#include <stdio.h>
#include <stdlib.h>
#include "vlc.h"
#include "../struct/constants.h"
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>

int vlc_socket = 0;
struct sockaddr_in vlc_addr;
char vlc_buffer[1024] = {0};

#define VLC_PORT 9988

char *vlc_read() {
    for (int i = 0; i < 1024; i++) {
        vlc_buffer[i] = 0;
    }
    read(vlc_socket, vlc_buffer, 1024);
    printf("vlc_read: %s\n", vlc_buffer);
    return vlc_buffer;
}

void vlc_connect() {
    if ((vlc_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("create");
    }

    vlc_addr.sin_family = AF_INET;
    vlc_addr.sin_port = htons(VLC_PORT);

    if (inet_pton(AF_INET, "127.0.0.1", &vlc_addr.sin_addr) <= 0) {
        perror("bind");
    }

    if (connect(vlc_socket, (struct sockaddr *) &vlc_addr, sizeof(vlc_addr)) < 0) {
        perror("connect");
    }

    vlc_read();
    vlc_read();
}

void vlc_send(char *message) {
    printf("vlc_send: %s", message);
    if (send(vlc_socket, message, strlen(message), 0) != strlen(message)) {
        perror("send");
    };
    vlc_read();
}

void vlc_action(char *action) {
    char message[100] = {0};
    sprintf(message, "%s\r\n", action);
    vlc_send(message);
}

#include <ctype.h>

int contains_digit(const char *s)
{
    while (*s) {
        if (isdigit(*s++) != 0) return 1;
    }

    return 0;
}

int vlc_get_seek_position() {
    char *message = "get_time\r\n";
    if (send(vlc_socket, message, strlen(message), 0) != strlen(message)) {
        perror("send");
    };

    char *read;
    do {
        read = vlc_read();
    } while (contains_digit(read) != 1);

    int position = atoi(read);
    return position;
}

void vlc_stop() {
    vlc_send("logout\r\n");
}