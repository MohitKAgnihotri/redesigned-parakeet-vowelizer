
#include <stddef.h>
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>
#include "command_handler.h"

static message_t *process_command_MERGE_VOWELS_BASIC( message_t *msg);
static message_t *process_command_SPLIT_VOWELS_BASIC( message_t *msg);
static message_t *process_command_MERGE_VOWELS_ADV( message_t *msg);
static message_t *process_command_SPLIT_VOWELS_ADV( message_t *msg);
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

static int check_num(char c)
{
    if (c == '1' || c == '2' || c == '3' || c == '4' || c == '5' || c == '6' || c =='7' || c =='8' || c == '9' || c == '0')
        return 1;

    return 0;
}


void advanced_merge_vowels(const char *consonant_string, const char *vowel_string, char *output_string)
{
    int v_count = 0;
    int nv_count = 0;
    int newstr_count = 0;

    int num_count = 0;
    int num;
    char text_num[20];

    while(vowel_string[v_count] != '\0')
    {
        // if we reach a numeric value (ex: '1') then convert to int
        if(check_num(vowel_string[v_count]))
        {
            text_num[num_count] = vowel_string[v_count];      // push to from v to tex_num
            v_count++;
            num_count++;
        }
        else
        {
            text_num[num_count] = '\0';
            num = atoi(text_num);           // converting numeric values in text_num to int
            num_count = 0;                  // resetting num count

            while(num > 0)                  // taking n number of values from nv
            {
                output_string[newstr_count] = consonant_string[nv_count];  // take value from nv and store in newstr
                newstr_count++;
                nv_count++;
                num--;
            }
            output_string[newstr_count] = vowel_string[v_count];        // take vowels from v and store to newstr
            newstr_count++;
            v_count++;
        }
    }
    output_string[newstr_count] = '\0';
    printf("merged string: %s \n", output_string);
}

void advanced_split_vowels(char *input_string, char *consonant_string, char *vowel_string)
{

    int i= 0;      // number of characters in user input
    int vowel_count = 0;
    int consonant_count = 0;
    int space_count = 0;
    char text_num[20] = {0};

    while(input_string[i]!='\0')
    {
        if (check_vowel(input_string[i]))    // check for vowels in the input string
        {
            sprintf(text_num, "%d", space_count);    // convert space count to string so we can concat it to string v
            vowel_string[vowel_count] = '\0';                       // we need string v to be a complete string so we can apply concat operation on it
            strcat(vowel_string,text_num);                      // concat space number that we need to skip to v string
            int num_len = strlen(text_num);          // length of the number text
            vowel_count = vowel_count + num_len;
            space_count = 0;                         // reset space count for next iteration

            vowel_string[vowel_count] = input_string[i];                     // adding the vowel in the end of string v
            vowel_count++;
        }
        else
        {
            consonant_string[consonant_count] = input_string[i];                   // add the non-vowels to string nv
            consonant_count++;
            space_count++;
        }
        i++;
    }
    consonant_string[consonant_count] = '\0';
    vowel_string[vowel_count] = '\0';

    printf("vowel: %s \n", vowel_string);
    printf("non-vowel: %s \n", consonant_string);
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

static message_t *process_command_MERGE_VOWELS_BASIC( message_t *msg)
{
    if (msg)
    {
        message_t *processed_message = (message_t *)malloc(sizeof(message_t));
        memset(processed_message, 0, sizeof(message_t));

        processed_message->type = COMMAND_RESPONSE;
        processed_message->command_id = MERGE_VOWELS_BASIC;

        command_merge_vowels_t *merge_vowels_cmd = (command_merge_vowels_t *)&msg->payload.command_merge_vowels;
        basic_merge_vowels(merge_vowels_cmd->consonants, merge_vowels_cmd->vowel, processed_message->payload.response_merge_vowels.output_string);
        return processed_message;
    }
}

static message_t *process_command_SPLIT_VOWELS_BASIC( message_t *msg)
{
    if (msg)
    {
        command_split_vowels_t *split_vowels    = (command_split_vowels_t *) &msg->payload.command_split_vowels;
        printf("split_vowels: %s \n", split_vowels->input_string);
        message_t *processed_message = (message_t *)malloc(sizeof(message_t));
        memset(processed_message, 0, sizeof(message_t));
        processed_message->type = COMMAND_RESPONSE;
        processed_message->command_id = SPLIT_VOWELS_ADV;
        basic_split_vowels(split_vowels->input_string, processed_message->payload.response_split_vowels.output_string_consonant, processed_message->payload.response_split_vowels.output_string_vowel);
        return processed_message;
    }
}

static message_t *process_command_MERGE_VOWELS_ADV( message_t *msg)
{
    if (msg)
    {
        message_t *processed_message = (message_t *)malloc(sizeof(message_t));
        memset(processed_message, 0, sizeof(message_t));
        processed_message->type = COMMAND_RESPONSE;
        processed_message->command_id = MERGE_VOWELS_BASIC;

        command_merge_vowels_t *merge_vowels_cmd = (command_merge_vowels_t *)&msg->payload.command_merge_vowels;
        advanced_merge_vowels(merge_vowels_cmd->consonants, merge_vowels_cmd->vowel, processed_message->payload.response_merge_vowels.output_string);
        return processed_message;
    }
}

static message_t *process_command_SPLIT_VOWELS_ADV( message_t *msg)
{
    if (msg)
    {
        command_split_vowels_t *split_vowels    = (command_split_vowels_t *) &msg->payload.command_split_vowels;
        printf("split_vowels: %s \n", split_vowels->input_string);
        message_t *processed_message = (message_t *)malloc(sizeof(message_t));
        memset(processed_message, 0, sizeof(message_t));
        processed_message->type = COMMAND_RESPONSE;
        processed_message->command_id = SPLIT_VOWELS_ADV;
        advanced_split_vowels(split_vowels->input_string,
                              processed_message->payload.response_split_vowels.output_string_consonant,
                              processed_message->payload.response_split_vowels.output_string_vowel);
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
        memset(processed_message, 0, sizeof(message_t));
        processed_message->type = COMMAND_RESPONSE;
        processed_message->command_id = SUPPORTED_COMMANDS;
        processed_message->payload.supported_commands.client_udp_port = supported_commands->client_udp_port;
        return processed_message;
    }
}

static message_t *process_command_Exit( message_t *msg)
{
    if (msg)
    {
        message_t *processed_message = (message_t *)malloc(sizeof(message_t));
        memset(processed_message, 0, sizeof(message_t));
        processed_message->type = COMMAND_RESPONSE;
        processed_message->command_id = EXIT;
        return processed_message;
    }
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
        case MERGE_VOWELS_BASIC:
            response = process_command_MERGE_VOWELS_BASIC(msg);
            break;
        case SPLIT_VOWELS_BASIC:
            response = process_command_SPLIT_VOWELS_BASIC(msg);
            break;
        case MERGE_VOWELS_ADV:
            response = process_command_MERGE_VOWELS_ADV(msg);
            break;
        case SPLIT_VOWELS_ADV:
            response = process_command_SPLIT_VOWELS_ADV(msg);
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
        case MERGE_VOWELS_BASIC:
        case MERGE_VOWELS_ADV:
            response = process_response_MERGE_VOWELS(msg);
            break;
        case SPLIT_VOWELS_BASIC:
        case SPLIT_VOWELS_ADV:
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