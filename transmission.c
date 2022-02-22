#include <string.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdbool.h>
#include "transmission.h"
#include "types.h"

static const char command_id_string[LAST_COMMAND][MAX_COMMAND_STRING_LENGTH] =
        {
                "MERGE_VOWELS",
                "SPLIT_VOWELS",
                "SUPPORTED_COMMANDS",
                "EXIT",
                "LAST_COMMAND"
        };

int receive_message_udp(int socket_fd, message_t *message)
{
    error_t result = ERR_SUCCESS;
    struct sockaddr from;
    unsigned int addrlen = sizeof(from);

    ssize_t bytes_received = recvfrom(socket_fd, message, sizeof(message_t), 0, &from, &addrlen);
    if (bytes_received == 0)
    {
        perror("send");
        printf("Error sending message, connection closed by the client\n");
        result  = ERR_RECV_CONN_CLOSED;
    } else if (bytes_received < 0)
    {
        perror("send");
        printf("Error sending message\n");
        result  = ERR_RECV_CONN_ERROR;
    }

    return result;
}

int send_message_udp(int socket_fd, message_t * message, struct sockaddr *to)
{
    error_t result = ERR_SUCCESS;
    unsigned int addrlen = sizeof(struct sockaddr);

    ssize_t bytes_sent = sendto(socket_fd, message, sizeof(message_t), 0, to, addrlen);
    if (bytes_sent == 0)
    {
        perror("send");
        printf("Error sending message, connection closed by the client\n");
        result  = ERR_RECV_CONN_CLOSED;
    } else if (bytes_sent < 0)
    {
        perror("send");
        printf("Error sending message\n");
        result  = ERR_RECV_CONN_ERROR;
    }

    return result;
}

int send_message_tcp(int socket_fd, message_t * message)
{
    error_t result = ERR_SUCCESS;
    ssize_t bytes_sent = send(socket_fd, message, sizeof(message_t), 0);
    if (bytes_sent == 0)
    {
        perror("send");
        printf("Error sending message, connection closed by the client\n");
        result  = ERR_SEND_CONN_CLOSED;
    } else if (bytes_sent < 0)
    {
        perror("send");
        printf("Error sending message\n");
        result  = ERR_SEND_CONN_ERROR;
    }

    return result;
}

int recv_message_tcp(int socket_fd, message_t * message)
{
    error_t result = ERR_SUCCESS;
    memset(message, 0, sizeof(message_t));
    ssize_t bytes_received = recv(socket_fd, message, sizeof(message_t), 0);
    if (bytes_received == 0)
    {
        perror("send");
        printf("Error sending message, connection closed by the client\n");
        result  = ERR_RECV_CONN_CLOSED;
    } else if (bytes_received < 0)
    {
        perror("send");
        printf("Error sending message\n");
        result  = ERR_RECV_CONN_ERROR;
    }

    return result;
}

int send_message_to_client_supported_commands(int client_socket, int port_number)
{
    message_t message;
    memset(&message, 0, sizeof(message_t));
    message.type = COMMAND_REQUEST;
    message.command_id = SUPPORTED_COMMANDS;

    for (int i = 1; ((i < LAST_COMMAND) && (i < MAX_SUPPORT_COMMANDS)); i++)
    {
        message.payload.supported_commands.command_id[i-1] = i;
        memcpy(message.payload.supported_commands.command_id_string[i-1], command_id_string[i-1], strlen(command_id_string[i-1]));
    }

    message.payload.supported_commands.number_of_commands = LAST_COMMAND - 1;
    message.payload.supported_commands.client_udp_port = port_number;

    send_message_tcp(client_socket, &message);
    return ERR_SUCCESS;
}


error_t setup_udp_socket(int port_number, int *client_udp_socket)
{
    int sockfd = 0;
    struct sockaddr_in servaddr;

    // Creating socket file descriptor
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
        perror("socket creation failed");
        *client_udp_socket = -1;
        return ERR_SOCKET_CREATION_FAILED;
    }

    memset(&servaddr, 0, sizeof(servaddr));

    // Filling server information
    servaddr.sin_family    = AF_INET; // IPv4
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(port_number);

    // Bind the socket with the server address
    if ( bind(sockfd, (const struct sockaddr *)&servaddr,
              sizeof(servaddr)) < 0 )
    {
        perror("bind failed");
        *client_udp_socket = -1;
        return ERR_SOCKET_BIND_FAILED;
    }

    *client_udp_socket = sockfd;
    return ERR_SUCCESS;
}

