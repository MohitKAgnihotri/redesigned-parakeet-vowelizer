
#include <stddef.h>
#include "command_handler.h"


static message_t *process_command_MERGE_VOWELS( message_t *msg);
static message_t *process_command_SPLIT_VOWELS( message_t *msg);
static message_t *process_command_SUPPORTED_COMMANDS( message_t *msg);
static message_t *process_command_Exit( message_t *msg);


static message_t *process_response_MERGE_VOWELS( message_t *msg);
static message_t *process_response_SPLIT_VOWELS( message_t *msg);
static message_t *process_response_SUPPORTED_COMMANDS( message_t *msg);
static message_t *process_response_Exit( message_t *msg);


static message_t *process_command_MERGE_VOWELS( message_t *msg)
{

}
static message_t *process_command_SPLIT_VOWELS( message_t *msg)
{

}
static message_t *process_command_SUPPORTED_COMMANDS( message_t *msg)
{

}
static message_t *process_command_Exit( message_t *msg)
{

}

static message_t *process_response_MERGE_VOWELS( message_t *msg)
{

}

static message_t *process_response_SPLIT_VOWELS( message_t *msg)
{

}

static message_t *process_response_SUPPORTED_COMMANDS( message_t *msg)
{

}

static message_t *process_response_Exit( message_t *msg)
{

}

message_t * process_command(message_t * msg) {
    message_t * response = NULL;
    switch (msg->command_id) {
        case MERGE_VOWELS:
            response = process_command_MERGE_VOWELS(msg);
            break;
        case SPLIT_VOWELS:
            response = process_command_SPLIT_VOWELS(msg);
            break;
        case SUPPORTED_COMMANDS:
            response = process_command_SUPPORTED_COMMANDS(msg);
            break;
        case EXIT:
            response = process_command_Exit(msg);
            break;
        default:
            break;
    }
    return response;
}

message_t * process_response(message_t * msg) {
    message_t * response = NULL;
    switch (msg->command_id) {
        case MERGE_VOWELS:
            response = process_response_MERGE_VOWELS(msg);
            break;
        case SPLIT_VOWELS:
            response = process_response_SPLIT_VOWELS(msg);
            break;
        case SUPPORTED_COMMANDS:
            response = process_response_SUPPORTED_COMMANDS(msg);
            break;
        case EXIT:
            response = process_response_Exit(msg);
            break;
        default:
            break;
    }
    return response;
}

message_t * process_message(message_t *message)
{
    if(message)
    {
        switch(message->type)
        {
            case COMMAND_REQUEST:
                return process_command(message);
            case COMMAND_RESPONSE:
                return process_response(message);
            default:
                return NULL;
        }
    }
}
