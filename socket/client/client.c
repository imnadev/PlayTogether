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

int sock = 0;
struct sockaddr_in serv_addr;
char client_buffer[1024] = {0};

int client_listening = FALSE;

void client_sync() {
    char *message;
    sprintf(message, "%s\r\n", SYNC);
    if (send(sock, message, strlen(message), 0) != strlen(message)) {
        perror("send");
    }
}

_Noreturn void *listen_to_server(void *) {
    while (client_listening) {
        memset(client_buffer, 0, sizeof(client_buffer));

        read(sock, client_buffer, 1024);

        if (strncmp(client_buffer, SERVER_STOP, sizeof(SERVER_STOP)) == 0) {
            main_window_on_exit_clicked();
            client_listening = FALSE;
        } else {
            vlc_send(client_buffer);
        }
    }
}

int client_init(char *ip, int port) {
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        return FAILURE;
    }

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