#include "client.h"
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <stdlib.h>
#include "../../vlc/vlc.h"
#include "../../screen/main/main_window.h"

int sock = 0, client_read;
struct sockaddr_in serv_addr;
char client_buffer[1024] = {0};

int client_listening = FALSE;

_Noreturn void *listen_to_server(void *) {
    while (client_listening) {
        memset(client_buffer, 0, sizeof(client_buffer));
        client_read = read(sock, client_buffer, 1024);

        if (strncmp(client_buffer, PLAY, sizeof(PLAY)) == 0) {
            vlc_action(PLAY);
        }

        if (strncmp(client_buffer, PAUSE, sizeof(PAUSE)) == 0) {
            vlc_action(PAUSE);
        }

        if (strncmp(client_buffer, SEEK_FORWARD, sizeof(SEEK_FORWARD)) == 0) {
            vlc_action(SEEK_FORWARD);
        }

        if (strncmp(client_buffer, SEEK_BACKWARD, sizeof(SEEK_BACKWARD)) == 0) {
            vlc_action(SEEK_BACKWARD);
        }

        if (strncmp(client_buffer, SET_SEEK, strlen(SET_SEEK)) == 0) {
            vlc_set_seek_position(atoi(client_buffer));
        }

        if (strncmp(client_buffer, SERVER_STOP, sizeof(SERVER_STOP)) == 0) {
            main_window_on_exit_clicked();
            client_listening = FALSE;
        }
    }
}

int client_init(char *ip, int port) {
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        return FAILURE;
    }

    memset(&serv_addr, '0', sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);

    if (inet_pton(AF_INET, ip, &serv_addr.sin_addr) <= 0) {
        return FAILURE;
    }

    if (connect(sock, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        return FAILURE;
    }

    client_listening = TRUE;
    pthread_t my_thread;
    pthread_create(&my_thread, NULL, listen_to_server, NULL);

    return SUCCESS;
}

void client_stop() {
    if (client_listening == TRUE) {
        client_listening = FALSE;
    }
}