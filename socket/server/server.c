#include "server.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/time.h>
#include <pthread.h>
#include "../../vlc/vlc.h"

#define PORT 8877

int master_socket, addrlen, new_socket, client_socket[30], max_clients = 30, activity, i, valread, sd, max_sd;
struct sockaddr_in address;
char buffer[1025];
fd_set readfds;
int listening = FALSE;

void server_action(char *action) {
    char message[100] = {0};

    if (strncmp(action, SYNC, sizeof(SYNC)) == 0) {
        int position = vlc_get_seek_position();
        sprintf(message, "seek %d\r\n", position);
        vlc_send(message);
    } else if (strncmp(action, SEEK_FORWARD, sizeof(SEEK_FORWARD)) == 0) {
        int position = vlc_get_seek_position() + 10;
        sprintf(message, "seek %d\r\n", position);
        vlc_send(message);
    } else if (strncmp(action, SEEK_BACKWARD, sizeof(SEEK_BACKWARD)) == 0) {
        int position = vlc_get_seek_position() - 10;
        if (position < 0) {
            position = 0;
        }
        sprintf(message, "seek %d\r\n", position);
        vlc_send(message);
    } else {
        sprintf(message, "%s\r\n", action);
    }

    for (i = 0; i < max_clients; i++) {
        if (client_socket[i] != 0) {
            if (send(client_socket[i], message, strlen(message), 0) != strlen(message)) {
                perror("send");
            }
        }
    }
}

_Noreturn void *listen_to_connections(void *) {
    while (listening) {
        FD_ZERO(&readfds);
        FD_SET(master_socket, &readfds);
        max_sd = master_socket;

        for (i = 0; i < max_clients; i++) {
            sd = client_socket[i];

            if (sd > 0) FD_SET(sd, &readfds);
            if (sd > max_sd) max_sd = sd;
        }

        activity = select(max_sd + 1, &readfds, NULL, NULL, NULL);

        if (FD_ISSET(master_socket, &readfds)) {
            if ((new_socket = accept(master_socket, (struct sockaddr *) &address, (socklen_t *) &addrlen)) < 0) {
                continue;
            }

            printf("New connection, socket fd is %d, ip is : %s, port : %d  \n",
                   new_socket,
                   inet_ntoa((address).sin_addr),
                   ntohs((address).sin_port)
            );

            for (i = 0; i < max_clients; i++) {
                if (client_socket[i] == 0) {
                    client_socket[i] = new_socket;
                    break;
                }
            }
        }

        for (i = 0; i < max_clients; i++) {
            sd = client_socket[i];

            if (FD_ISSET(sd, &readfds)) {
                if ((valread = read(sd, buffer, 1024)) == 0) {

                    if (strncmp(buffer, SYNC, sizeof(SYNC)) == 0) {
                        int position = vlc_get_seek_position();

                        char *message;
                        sprintf(message, "seek %d\r\n", position);

                        if (send(sd, message, strlen(message), 0) != strlen(message)) {
                            perror("send");
                        }
                    } else {
                        getpeername(sd, (struct sockaddr *) &address, (socklen_t *) addrlen);

                        printf("Host disconnected, ip %s, port %d \n",
                               inet_ntoa((address).sin_addr),
                               ntohs((address).sin_port)
                        );

                        close(sd);
                        client_socket[i] = 0;
                    }
                }

            }
        }
    }
}

int server_init() {
    for (i = 0; i < max_clients; i++) {
        client_socket[i] = 0;
    }

    if (master_socket == 0) {
        if ((master_socket = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
            perror("create");
            return FAILURE;
        }

        address.sin_family = AF_INET;
        address.sin_addr.s_addr = INADDR_ANY;
        address.sin_port = htons(PORT);

        if (bind(master_socket, (struct sockaddr *) &address, sizeof(address)) < 0) {
            perror("bind");
            return FAILURE;
        }

        if (listen(master_socket, 3) < 0) {
            perror("listen");
            return FAILURE;
        }

        addrlen = sizeof(address);
    }

    listening = TRUE;

    pthread_t my_thread;
    pthread_create(&my_thread, NULL, listen_to_connections, NULL);

    return SUCCESS;
}

void server_stop() {
    if (listening == TRUE) {
        server_action(SERVER_STOP);
        listening = FALSE;
    }
}