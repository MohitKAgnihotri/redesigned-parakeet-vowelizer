#include "client.h"
#include "types.h"
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/socket.h>
#include <unistd.h>
#include <stdbool.h>

#include "transmission.h"
#include "command_handler.h"
#include "user_interface.h"
#include "types.h"

#define SERVER_NAME_LEN_MAX 255


int client_udp_port_number = 0;

int main(int argc, char *argv[])
{
    char server_name[SERVER_NAME_LEN_MAX + 1] = {0};
    int server_tcp_port, socket_fd_tcp;
    int server_udp_port, socket_fd_udp;
    struct hostent *server_host;
    struct sockaddr_in server_address;
    bool exit_is_requested = false;

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
    if ((socket_fd_tcp = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        exit(1);
    }

    /* Connect to socket with server address. */
    if (connect(socket_fd_tcp, (struct sockaddr *) &server_address, sizeof server_address) == -1) {
        perror("connect");
        exit(1);
    }

    // receive set of supported commands & UDP port Number
    message_t incoming_message;
    error_t  status = recv_message_tcp(socket_fd_tcp, &incoming_message);
    if (status != ERR_SUCCESS)
    {
        fprintf(stderr, "Error receiving message: %d\n", status);
        exit(EXIT_FAILURE);
    }

    message_t *processed_message  = process_message(&incoming_message);
    if (processed_message == NULL)
    {
        fprintf(stderr, "Error processing message\n");
        exit(EXIT_FAILURE);
    }

    if (processed_message->type == COMMAND_RESPONSE && processed_message->command_id == SUPPORTED_COMMANDS)
    {
        client_udp_port_number = processed_message->payload.supported_commands.client_udp_port;
    }

    setup_udp_socket(client_udp_port_number, &socket_fd_udp);

    while (!exit_is_requested)
    {
        message_t outgoing_message;
        print_user_menu();
        int choice = get_user_choice();
        switch (choice) {
            case 1:
                outgoing_message.type = COMMAND_REQUEST;
                outgoing_message.command_id = SPLIT_VOWELS;
                printf("Enter the string to denvowel \n");
                get_line_from_stdin(outgoing_message.payload.command_split_vowels.input_string, MAX_STRING_LENGTH);
                status = send_message_tcp(socket_fd_tcp, &outgoing_message);
                if (status != ERR_SUCCESS)
                {
                    fprintf(stderr, "Error sending message: %d\n", status);
                    exit(EXIT_FAILURE);
                }

                status = recv_message_tcp(socket_fd_tcp, &incoming_message);
                if (status != ERR_SUCCESS)
                {
                    fprintf(stderr, "Error receiving message: %d\n", status);
                    exit(EXIT_FAILURE);
                }
                else
                {
                    printf("consonants: :%s:\n", incoming_message.payload.response_split_vowels.output_string_consonant);
                }

                status = receive_message_udp(socket_fd_udp, &incoming_message);
                if (status != ERR_SUCCESS)
                {
                    fprintf(stderr, "Error receiving message: %d\n", status);
                    exit(EXIT_FAILURE);
                }
                else
                {
                    printf("vowels: :%s:\n", incoming_message.payload.response_split_vowels.output_string_vowel);
                }
                break;
            case 2:
                outgoing_message.type = COMMAND_REQUEST;
                outgoing_message.command_id = MERGE_VOWELS;

                printf("Enter the consonant part of the string to envowel \n");
                get_line_from_stdin(outgoing_message.payload.command_merge_vowels.consonants, MAX_STRING_LENGTH);

                printf("Enter the vowel part of the string to envowel \n");
                get_line_from_stdin(outgoing_message.payload.command_merge_vowels.vowel, MAX_STRING_LENGTH);

                status = send_message_tcp(socket_fd_tcp, &outgoing_message);
                if (status != ERR_SUCCESS)
                {
                    fprintf(stderr, "Error sending message: %d\n", status);
                    exit(EXIT_FAILURE);
                }

                status = recv_message_tcp(socket_fd_tcp, &incoming_message);
                if (status != ERR_SUCCESS)
                {
                    fprintf(stderr, "Error receiving message: %d\n", status);
                    exit(EXIT_FAILURE);
                }
                else
                {
                    printf("envoweled string: %s\n", incoming_message.payload.response_merge_vowels.output_string);
                }
                break;
            case 3:
                outgoing_message.type = COMMAND_REQUEST;
                outgoing_message.command_id = SPLIT_VOWELS;
                printf("Enter the string to denvowel \n");
                get_line_from_stdin(outgoing_message.payload.command_split_vowels.input_string, MAX_STRING_LENGTH);
                status = send_message_tcp(socket_fd_tcp, &outgoing_message);
                if (status != ERR_SUCCESS)
                {
                    fprintf(stderr, "Error sending message: %d\n", status);
                    exit(EXIT_FAILURE);
                }

                status = recv_message_tcp(socket_fd_tcp, &incoming_message);
                if (status != ERR_SUCCESS)
                {
                    fprintf(stderr, "Error receiving message: %d\n", status);
                    exit(EXIT_FAILURE);
                }
                else
                {
                    printf("consonants: %s\n", incoming_message.payload.response_split_vowels.output_string_consonant);
                }
                status = receive_message_udp(socket_fd_udp, &incoming_message);
                if (status != ERR_SUCCESS)
                {
                    fprintf(stderr, "Error receiving message: %d\n", status);
                    exit(EXIT_FAILURE);
                }
                else
                {
                    printf("vowels: %s\n", incoming_message.payload.response_split_vowels.output_string_vowel);
                }
                break;
            case 4:
                outgoing_message.type = COMMAND_REQUEST;
                outgoing_message.command_id = MERGE_VOWELS;

                printf("Enter the consonant part of the string to envowel \n");
                get_line_from_stdin(outgoing_message.payload.command_merge_vowels.consonants, MAX_STRING_LENGTH);

                printf("Enter the vowel part of the string to envowel \n");
                get_line_from_stdin(outgoing_message.payload.command_merge_vowels.vowel, MAX_STRING_LENGTH);

                status = send_message_tcp(socket_fd_tcp, &outgoing_message);
                if (status != ERR_SUCCESS)
                {
                    fprintf(stderr, "Error sending message: %d\n", status);
                    exit(EXIT_FAILURE);
                }

                status = recv_message_tcp(socket_fd_tcp, &incoming_message);
                if (status != ERR_SUCCESS)
                {
                    fprintf(stderr, "Error receiving message: %d\n", status);
                    exit(EXIT_FAILURE);
                }
                else
                {
                    printf("envoweled string: %s\n", incoming_message.payload.response_merge_vowels.output_string);
                }
                break;
            case 5:
                exit_is_requested = true;
                break;
            default:
                exit_is_requested = true;
                break;
        }
    }

    close(socket_fd_tcp);
    close(socket_fd_udp);
    return 0;
}