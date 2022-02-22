cmake_minimum_required(VERSION 3.16)
project(redesigned_parakeet_vowelizer C)

set(CMAKE_C_STANDARD 11)

link_libraries(pthread)

add_executable(server_vowelizer server.c server.h types.h transmission.c transmission.h command_handler.c command_handler.h)
add_executable(client_vowelizer types.h transmission.c transmission.h client.c client.h command_handler.c command_handler.h user_interface.c user_interface.h)
