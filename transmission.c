#include <string.h>
#include "transmission.h"
#include "types.h"

int send_message_to_client_supported_commands(int client_socket)
{
    message_t message;
    message.type = COMMAND_REQUEST;
    message.command_id = SUPPORTED_COMMANDS;

    for (int i = 0; i < LAST_COMMAND; i++)
    {
        message.payload.supported_commands.command_id[i] = i;
        memcpy(message.payload.supported_commands.command_id_string[i], command_id_string[i], strlen(command_id_string[i]));
    }
    message.payload.supported_commands.number_of_commands = LAST_COMMAND - 1;
}
