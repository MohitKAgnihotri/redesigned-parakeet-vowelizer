#include <netinet/in.h>
#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdbool.h>
#include "server.h"
#include "transmission.h"
#include "command_handler.h"
#include "types.h"

#define BACKLOG 10
#define PORT_NUM 1313


/* Thread routine to serve connection to client. */
void *pthread_routine(void *arg);

/* Signal handler to handle SIGTERM and SIGINT signals. */
void signal_handler(int signal_number);

void SetupSignalHandler();

int CreateServerSocket(int port);

int server_socket_fd;
static int client_number;

int main(int argc, char *argv[])
{
    int port, new_socket_fd;
    pthread_attr_t pthread_client_attr;
    pthread_t pthread;
    socklen_t client_address_len;
    struct sockaddr_in client_address;

    /* Get port from command line arguments or stdin.
     * For this server, this is fixed to 1113*/
    port = PORT_NUM;

    /*Create the server socket */
    server_socket_fd = CreateServerSocket(port);

    /*Setup the signal handler*/
    SetupSignalHandler();

    /* Initialise pthread attribute to create detached threads. */
    if (pthread_attr_init(&pthread_client_attr) != 0) {
        perror("pthread_attr_init");
        exit(1);
    }

    if (pthread_attr_setdetachstate(&pthread_client_attr, PTHREAD_CREATE_DETACHED) != 0) {
        perror("pthread_attr_setdetachstate");
        exit(1);
    }

    while (1) {

        /* Accept connection to client. */
        client_address_len = sizeof (client_address);
        new_socket_fd = accept(server_socket_fd, (struct sockaddr *)&client_address, &client_address_len);
        if (new_socket_fd == -1) {
            perror("accept");
            continue;
        }

        printf("Client connected\n");
        pthread_args_t *thread_arg = (pthread_args_t *) malloc(sizeof(pthread_args_t));
        thread_arg->client_socket_fd = new_socket_fd;
        thread_arg->client_id = client_number++;

        /* Create thread to serve connection to client. */
        if (pthread_create(&pthread, &pthread_client_attr, pthread_routine, (void *)thread_arg) != 0) {
            perror("pthread_create");
            continue;
        }
    }

    return 0;
}


int CreateServerSocket(int port)
{
    struct sockaddr_in address;
    int socket_fd;

    /* Initialise IPv4 address. */
    memset(&address, 0, sizeof (address));
    address.sin_family = AF_INET;
    address.sin_port = htons(port);
    address.sin_addr.s_addr = INADDR_ANY;

    /* Create TCP socket. */
    if ((socket_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("socket");
        exit(1);
    }

    /* Bind address to socket. */
    if (bind(socket_fd, (struct sockaddr *)&address, sizeof (address)) == -1) {
        perror("bind");
        exit(1);
    }

    /* Listen on socket. */
    if (listen(socket_fd, BACKLOG) == -1) {
        perror("listen");
        exit(1);
    }

    // Configure server socket
    int enable = 1;
    setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(enable));
    return socket_fd;
}

void SetupSignalHandler() {/* Assign signal handlers to signals. */
    if (signal(SIGPIPE, SIG_IGN) == SIG_ERR) {
        perror("signal");
        exit(1);
    }
    if (signal(SIGTERM, signal_handler) == SIG_ERR) {
        perror("signal");
        exit(1);
    }
    if (signal(SIGINT, signal_handler) == SIG_ERR) {
        perror("signal");
        exit(1);
    }
}

void *pthread_routine(void *arg)
{
    int server_udp_socket_fd;

    pthread_args_t *thread_argument = (pthread_args_t*) arg;
    int client_tcp_socket_fd = thread_argument->client_socket_fd;
    int client_port_number = thread_argument->client_id + UDP_PORT_OFFSET_CLIENT;
    int server_port_number = thread_argument->client_id + UDP_PORT_OFFSET_SERVER;
    free(arg);

    bool is_exit_requested = false;

    send_message_to_client_supported_commands(client_tcp_socket_fd, client_port_number);
    setup_udp_socket(server_port_number, &server_udp_socket_fd);

    while (!is_exit_requested)
    {
        message_t message;
        recv_message_tcp(client_tcp_socket_fd, &message);
        message_t * processed_message = process_message(&message);
        if (processed_message->type == COMMAND_RESPONSE && processed_message->command_id == EXIT)
        {
            is_exit_requested = true;
        }
        else
        {
            send_message_tcp(client_tcp_socket_fd, processed_message);
            if (processed_message->type == COMMAND_RESPONSE &&
                    (processed_message->command_id == SPLIT_VOWELS_BASIC || processed_message->command_id == SPLIT_VOWELS_ADV))
            {
                struct sockaddr_in to_client;
                to_client.sin_family = AF_INET;
                to_client.sin_port = htons(client_port_number);
                to_client.sin_addr.s_addr = htonl(INADDR_ANY);
                if (inet_pton(AF_INET, "127.0.0.1", &to_client.sin_addr.s_addr)==0)
                {
                    printf("inet_pton() failed\n");
                    pthread_exit(NULL);
                }

                send_message_udp(server_udp_socket_fd, processed_message, (struct sockaddr *) &to_client);
            }
        }
        free(processed_message);
    }

    close(client_tcp_socket_fd);
    close(server_udp_socket_fd);

    return NULL;
}

void signal_handler(int signal_number)
{
    close(server_socket_fd);
    exit(0);
}