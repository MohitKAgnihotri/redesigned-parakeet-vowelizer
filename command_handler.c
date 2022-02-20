
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


static int check_vowel(char c)
{
    if (c == 'a' || c == 'A' || c == 'e' || c == 'E' || c == 'i' || c == 'I' || c =='o' || c =='O' || c == 'u' || c == 'U')
        return 1;

    return 0;
}

void basic_split_vowels(char *input_string, char *consonant_string, char *vowel_string)
{
    int i= 0;      // number of characters in user input
    while(input_string[i]!='\0' && i < MAX_STRING_LENGTH)
    {
        if (check_vowel(input_string[i]))    // check for vowels in the input string
        {
            vowel_string[i] = input_string[i];          // input string will contain vowels only
            consonant_string[i] = ' ';            // non vowels are denoted by a space
        }
        else
        {
            consonant_string[i] = input_string[i];         // input string will contain non vowels only
            vowel_string[i] = ' ';             // vowels are denoted by a space
        }
        i++;
    }
    consonant_string[i] = '\0';
    vowel_string[i] = '\0';

    printf("vowel: %s \n", vowel_string);
    printf("non-vowel: %s \n", consonant_string);
}

static void basic_merge_vowels(const char *consonant_string, const char *vowel_string, char *output_string)
{
    int i= 0;      // number of characters in the input string
    while(vowel_string[i]!='\0' && i < MAX_STRING_LENGTH)          // loop until the end of the length of the input string containing non-vowels
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
        basic_merge_vowels(merge_vowels_cmd->consonants, merge_vowels_cmd->vowel, processed_message->payload.response_merge_vowels.output_string);
        return processed_message;
    }
}

static message_t *process_command_SPLIT_VOWELS( message_t *msg)
{
    if (msg)
    {
        command_split_vowels_t *split_vowels    = (command_split_vowels_t *) &msg->payload.command_split_vowels;
        printf("split_vowels: %s \n", split_vowels->input_string);
        message_t *processed_message = (message_t *)malloc(sizeof(message_t));
        processed_message->type = COMMAND_RESPONSE;
        processed_message->command_id = SPLIT_VOWELS;
        basic_split_vowels(split_vowels->input_string, processed_message->payload.response_split_vowels.output_string_consonant, processed_message->payload.response_split_vowels.output_string_vowel);
        return processed_message;
    }
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
        message_t *processed_message = (message_t *)malloc(sizeof(message_t));
        processed_message->type = COMMAND_RESPONSE;
        processed_message->command_id = SUPPORTED_COMMANDS;
        processed_message->payload.supported_commands.client_udp_port = supported_commands->client_udp_port;
        return processed_message;
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

message_t * process_request(message_t * msg) {
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
                return process_request(message);
            case COMMAND_RESPONSE:
                return process_response(message);
            default:
                return NULL;
        }
    }
}