#include "client.h"
#include "types.h"
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/socket.h>
#include <unistd.h>

#include "transmission.h"
#include "command_handler.h"

#define SERVER_NAME_LEN_MAX 255

int main(int argc, char *argv[])
{
    char server_name[SERVER_NAME_LEN_MAX + 1] = {0};
    int server_tcp_port, socket_fd;
    int server_udp_port;
    struct hostent *server_host;
    struct sockaddr_in server_address;

    if (argc < 3)
    {
        fprintf(stderr, "Usage: %s <server_name> <server_tcp_port> <server_udp_port>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    /* Get server name from command line arguments or stdin. */
    strncpy(server_name, argv[1], SERVER_NAME_LEN_MAX);

    /* Get server port from command line arguments or stdin. */
    server_tcp_port = atoi(argv[2]);
    if (server_tcp_port == 0)
    {
        fprintf(stderr, "Invalid server TCP port: %s\n", argv[2]);
        exit(EXIT_FAILURE);
    }

    /* Get server port from command line arguments or stdin. */
    server_udp_port = atoi(argv[3]);
    if (server_udp_port == 0)
    {
        fprintf(stderr, "Invalid server UDP port: %s\n", argv[3]);
        exit(EXIT_FAILURE);
    }

    /* Get server host from server name. */
    server_host = gethostbyname(server_name);

    /* Initialise IPv4 server address with server host. */
    memset(&server_address, 0, sizeof server_address);
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(server_tcp_port);
    memcpy(&server_address.sin_addr.s_addr, server_host->h_addr, server_host->h_length);

    /* Create TCP socket. */
    if ((socket_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        exit(1);
    }

    /* Connect to socket with server address. */
    if (connect(socket_fd, (struct sockaddr *) &server_address, sizeof server_address) == -1) {
        perror("connect");
        exit(1);
    }

    // receive set of supported commands & UDP port Number
    message_t message;
    error_t  status = recv_message_tcp(socket_fd, &message);
    if (status != ERR_SUCCESS)
    {
        fprintf(stderr, "Error receiving message: %d\n", status);
        exit(EXIT_FAILURE);
    }

    message_t processed_message process_message(&message);


    close(socket_fd);
    return 0;
}