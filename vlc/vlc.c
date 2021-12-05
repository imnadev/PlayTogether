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

void * vlc_connect() {
    printf("connecting");
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
    printf("connected");
}

void vlc_send(char * message) {
    printf("vlc_send: %s", message);
    if(send(vlc_socket, message, strlen(message), 0) != strlen(message)) {
        perror("send");
    };
}

void vlc_action(char * action) {
    char *message;
    if (strncmp(action, SEEK_FORWARD, sizeof(SEEK_FORWARD)) == 0) {
        int position = vlc_get_seek_position() + 10;
        sprintf(message, "seek %d\r\n", position);
    } else if (strncmp(action, SEEK_BACKWARD, sizeof(SEEK_BACKWARD)) == 0) {
        int position = vlc_get_seek_position() - 10;
        sprintf(message, "seek %d\r\n", position);
    } else {
        message = action;
    }
    vlc_send(action);
}

int vlc_get_seek_position() {
    vlc_action("get_time\r\n");
    read(vlc_socket, vlc_buffer, 1024);
    printf("time: %s", vlc_buffer);
    return atoi(vlc_buffer);
}

void vlc_stop() {
    vlc_send("shutdown");
}