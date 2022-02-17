#include "types.h"

#ifndef REDESIGNED_PARAKEET_VOWELIZER_TRANSMISSION_H
#define REDESIGNED_PARAKEET_VOWELIZER_TRANSMISSION_H

int send_message_to_client_supported_commands(int client_socket);

int receive_message_from_client(int client_socket);

message_t * process_message_from_client(int client_socket);

int send_message_to_client(message_t * message, int client_socket);

#endif //REDESIGNED_PARAKEET_VOWELIZER_TRANSMISSION_H
