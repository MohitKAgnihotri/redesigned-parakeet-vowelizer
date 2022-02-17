

#ifndef REDESIGNED_PARAKEET_VOWELIZER_TYPES_H
#define REDESIGNED_PARAKEET_VOWELIZER_TYPES_H

#define MAX_STRING_LENGTH 1024
#define MAX_SUPPORT_COMMANDS 4
#define MAX_COMMAND_STRING_LENGTH 128


typedef enum error
{
    ERR_SUCCESS = 0,
    ERR_FAILURE = 1,
} error_t;

typedef enum command_id
{
    MERGE_VOWELS = 1,
    SPLIT_VOWELS = 2,
    EXIT = 3,
    SUPPORTED_COMMANDS = 4,
    LAST_COMMAND = 5
}command_id_t;

const char command_id_string[LAST_COMMAND][MAX_COMMAND_STRING_LENGTH] =
{
    "MERGE_VOWELS",
    "SPLIT_VOWELS",
    "EXIT",
    "SUPPORTED_COMMANDS",
    "LAST_COMMAND"
};

typedef enum message_type
{
    COMMAND_REQUEST = 1,
    COMMAND_RESPONSE = 2,
    LAST_MESSAGE_TYPE = 3
}message_type_t;

typedef struct command_supported {
    int number_of_commands;
    int command_id[MAX_SUPPORT_COMMANDS];
    char command_id_string[MAX_SUPPORT_COMMANDS][MAX_COMMAND_STRING_LENGTH];
}supported_commands_t;

typedef struct command_merge_vowels {
    char word[MAX_STRING_LENGTH];
    char vowel[MAX_STRING_LENGTH];
}command_merge_vowels_t;

typedef struct command_split_vowels {
    char input_string[MAX_STRING_LENGTH];
}command_split_vowels_t;

typedef struct response_merge_vowels {
    char output_string[MAX_STRING_LENGTH];
}response_merge_vowels_t;

typedef struct response_split_vowels {
    char output_string_consonant[MAX_STRING_LENGTH];
    char output_string_vowel[MAX_STRING_LENGTH];
}response_split_vowels_t;


typedef struct message
{
    message_type_t type;
    command_id_t command_id;
    union {
        supported_commands_t supported_commands;
        command_merge_vowels_t command_merge_vowels;
        command_split_vowels_t command_split_vowels;
        response_merge_vowels_t response_merge_vowels;
        response_split_vowels_t response_split_vowels;
    } payload;
}message_t;


#endif //REDESIGNED_PARAKEET_VOWELIZER_TYPES_H
