
#include <stddef.h>
#include <stdio.h>
#include <malloc.h>
#include "command_handler.h"


static message_t *process_command_MERGE_VOWELS( message_t *msg);
static message_t *process_command_SPLIT_VOWELS( message_t *msg);
static message_t *process_command_SUPPORTED_COMMANDS( message_t *msg);
static message_t *process_command_Exit( message_t *msg);

static message_t *process_response_MERGE_VOWELS( message_t *msg);
static message_t *process_response_SPLIT_VOWELS( message_t *msg);
static message_t *process_response_SUPPORTED_COMMANDS( message_t *msg);
static message_t *process_response_Exit( message_t *msg);


static void envowel(char *consonant_string, char *vowel_string, char *output_string)
{
    int i= 0;      // number of characters in the input string
    while(vowel_string[i]!='\0')          // loop until the end of the length of the input string containing non-vowels
    {
        if (vowel_string[i] != ' ')         // check if index of the string in v is not a space
        {
            output_string[i] = vowel_string[i];      // store vowel in the new merged string
        }
        else
        {
            output_string[i] = consonant_string[i];     // store non vowels in the new merged string
        }
        i++;
    }
    output_string[i] = '\0';
    printf("merged string: %s \n", output_string);
}

static message_t *process_command_MERGE_VOWELS( message_t *msg)
{
    if (msg)
    {
        message_t *processed_message = (message_t *)malloc(sizeof(message_t));
        processed_message->type = COMMAND_RESPONSE;
        processed_message->command_id = MERGE_VOWELS;

        command_merge_vowels_t *merge_vowels_cmd = (command_merge_vowels_t *)&msg->payload.command_merge_vowels;
        envowel(merge_vowels_cmd->consonants, merge_vowels_cmd->vowel, processed_message->payload.response_merge_vowels.output_string);
        return processed_message;
    }
}

static message_t *process_command_SPLIT_VOWELS( message_t *msg)
{

}
static message_t *process_command_SUPPORTED_COMMANDS( message_t *msg)
{
    if (msg)
    {
        supported_commands_t *supported_commands = (supported_commands_t *) &msg->payload.supported_commands;
        printf("Supported Server Commands\n");
        for (int i = 0; i < supported_commands->number_of_commands; i++) {
            printf("Command String = %s, Command Id = %d\n", supported_commands->command_id_string[i],
                   supported_commands->command_id[i]);
        }
        printf("Port Number for UDP Comunication = %d \n", supported_commands->client_udp_port);
    }
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
