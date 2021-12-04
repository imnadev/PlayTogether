#include "server.h"
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/time.h>
#include <pthread.h>

#define PORT 8888

int master_socket, addrlen, new_socket, client_socket[30], max_clients = 30, activity, i, valread, sd, max_sd;
struct sockaddr_in address;
char buffer[1025];
fd_set readfds;
char *message = "ECHO Daemon v1.0 \r\n";

void server_action(char *action) {
    for (i = 0; i < max_clients; i++) {
        if (client_socket[i] != 0) {
            if (send(client_socket[i], action, strlen(action), 0) != strlen(action)) {
                perror("send");
            }
        }
    }
}

_Noreturn void *listen_to_connections(void *) {
    while (TRUE) {
        FD_ZERO(&readfds);                  //clear the socket set
        FD_SET(master_socket, &readfds);    //add master socket to set
        max_sd = master_socket;

        for (i = 0; i < max_clients; i++) {
            sd = client_socket[i];  //socket descriptor

            if (sd > 0) FD_SET(sd, &readfds);   //if valid socket descriptor then add to read list
            if (sd > max_sd) max_sd = sd;       //highest file descriptor number, need it for the select function
        }

        //wait for an activity on one of the sockets
        activity = select(max_sd + 1, &readfds, NULL, NULL, NULL);

        if ((activity < 0) && (errno != EINTR)) printf("select error");

        //Incoming connection
        if (FD_ISSET(master_socket, &readfds)) {
            if ((new_socket = accept(master_socket, (struct sockaddr *) &address, (socklen_t *) &addrlen)) < 0) {
                perror("accept");
                continue;
            }


            //inform user of socket number - used in send and receive commands
            printf("New connection, socket fd is %d, ip is : %s, port : %d  \n",
                   new_socket,
                   inet_ntoa((address).sin_addr),
                   ntohs((address).sin_port)
            );

            //send new connection greeting message
            if (send(new_socket, message, strlen(message), 0) != strlen(message)) {
                perror("send");
            }
            puts("Welcome message sent successfully");

            //add new socket to array of sockets
            for (i = 0; i < max_clients; i++) {
                //if position is empty
                if (client_socket[i] == 0) {
                    client_socket[i] = new_socket;
                    printf("Adding to list of sockets as %d\n", i);
                    break;
                }
            }
        }

        //else its some IO operation on some other socket
        for (i = 0; i < max_clients; i++) {
            sd = client_socket[i];

            if (FD_ISSET(sd, &readfds)) {
                //Check if it was for closing, and also read the incoming message
                if ((valread = read(sd, buffer, 1024)) == 0) {
                    //Somebody disconnected, get his details and print
                    getpeername(sd, (struct sockaddr *) &address, (socklen_t *) addrlen);

                    printf("Host disconnected, ip %s, port %d \n",
                           inet_ntoa((address).sin_addr),
                           ntohs((address).sin_port)
                    );

                    //Close the socket and mark as 0 in list for reuse
                    close(sd);
                    client_socket[i] = 0;
                }
                    //Echo back the message that came in
                else {
                    //set the string terminating NULL byte on the end of the data read
                    buffer[valread] = '\0';
                    send(sd, buffer, strlen(buffer), 0);
                }
            }
        }
    }
}

int server_init() {
    for (i = 0; i < max_clients; i++) {     //initialise all client_socket[] to 0 so not checked
        client_socket[i] = 0;
    }

    if ((master_socket = socket(AF_INET, SOCK_STREAM, 0)) == 0) {   //create a master socket
        perror("Socket creation failed");
        return FAILURE;
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(master_socket, (struct sockaddr *) &address, sizeof(address)) <
        0) {   //bind theSEEK_BACKWARD socket to localhost port 8888
        perror("bind failed");
        return FAILURE;
    }

    printf("Listener on port %d \n", PORT);
    if (listen(master_socket, 3) < 0) {     //try to specify maximum of 3 pending connections for the master socket
        perror("listen");
        return FAILURE;
    }

    addrlen = sizeof(address);
    puts("Waiting for connections ...");

    pthread_t my_thread;
    pthread_create(&my_thread, NULL, listen_to_connections, NULL);

    return SUCCESS;
}