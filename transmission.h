#include "types.h"

#ifndef REDESIGNED_PARAKEET_VOWELIZER_TRANSMISSION_H
#define REDESIGNED_PARAKEET_VOWELIZER_TRANSMISSION_H

int send_message_to_client_supported_commands(int client_socket, int client_id);

int recv_message_tcp(int socket_fd, message_t * message);
int send_message_tcp(int socket_fd, message_t * message);

int receive_message_udp(int socket_fd, message_t *message);
int send_message_udp(int socket_fd, message_t * message);

error_t setup_client_udp_socket(int client_id, int *client_udp_socket);

#endif //REDESIGNED_PARAKEET_VOWELIZER_TRANSMISSION_H
