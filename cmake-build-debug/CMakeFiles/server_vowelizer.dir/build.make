# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /mnt/c/Workspace/Chegg/2022/redesigned-parakeet-vowelizer

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/c/Workspace/Chegg/2022/redesigned-parakeet-vowelizer/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/server_vowelizer.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/server_vowelizer.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/server_vowelizer.dir/flags.make

CMakeFiles/server_vowelizer.dir/server.c.o: CMakeFiles/server_vowelizer.dir/flags.make
CMakeFiles/server_vowelizer.dir/server.c.o: ../server.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Workspace/Chegg/2022/redesigned-parakeet-vowelizer/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/server_vowelizer.dir/server.c.o"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/server_vowelizer.dir/server.c.o   -c /mnt/c/Workspace/Chegg/2022/redesigned-parakeet-vowelizer/server.c

CMakeFiles/server_vowelizer.dir/server.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/server_vowelizer.dir/server.c.i"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/c/Workspace/Chegg/2022/redesigned-parakeet-vowelizer/server.c > CMakeFiles/server_vowelizer.dir/server.c.i

CMakeFiles/server_vowelizer.dir/server.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/server_vowelizer.dir/server.c.s"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/c/Workspace/Chegg/2022/redesigned-parakeet-vowelizer/server.c -o CMakeFiles/server_vowelizer.dir/server.c.s

CMakeFiles/server_vowelizer.dir/transmission.c.o: CMakeFiles/server_vowelizer.dir/flags.make
CMakeFiles/server_vowelizer.dir/transmission.c.o: ../transmission.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Workspace/Chegg/2022/redesigned-parakeet-vowelizer/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/server_vowelizer.dir/transmission.c.o"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/server_vowelizer.dir/transmission.c.o   -c /mnt/c/Workspace/Chegg/2022/redesigned-parakeet-vowelizer/transmission.c

CMakeFiles/server_vowelizer.dir/transmission.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/server_vowelizer.dir/transmission.c.i"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/c/Workspace/Chegg/2022/redesigned-parakeet-vowelizer/transmission.c > CMakeFiles/server_vowelizer.dir/transmission.c.i

CMakeFiles/server_vowelizer.dir/transmission.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/server_vowelizer.dir/transmission.c.s"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/c/Workspace/Chegg/2022/redesigned-parakeet-vowelizer/transmission.c -o CMakeFiles/server_vowelizer.dir/transmission.c.s

CMakeFiles/server_vowelizer.dir/command_handler.c.o: CMakeFiles/server_vowelizer.dir/flags.make
CMakeFiles/server_vowelizer.dir/command_handler.c.o: ../command_handler.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Workspace/Chegg/2022/redesigned-parakeet-vowelizer/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/server_vowelizer.dir/command_handler.c.o"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/server_vowelizer.dir/command_handler.c.o   -c /mnt/c/Workspace/Chegg/2022/redesigned-parakeet-vowelizer/command_handler.c

CMakeFiles/server_vowelizer.dir/command_handler.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/server_vowelizer.dir/command_handler.c.i"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/c/Workspace/Chegg/2022/redesigned-parakeet-vowelizer/command_handler.c > CMakeFiles/server_vowelizer.dir/command_handler.c.i

CMakeFiles/server_vowelizer.dir/command_handler.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/server_vowelizer.dir/command_handler.c.s"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/c/Workspace/Chegg/2022/redesigned-parakeet-vowelizer/command_handler.c -o CMakeFiles/server_vowelizer.dir/command_handler.c.s

# Object files for target server_vowelizer
server_vowelizer_OBJECTS = \
"CMakeFiles/server_vowelizer.dir/server.c.o" \
"CMakeFiles/server_vowelizer.dir/transmission.c.o" \
"CMakeFiles/server_vowelizer.dir/command_handler.c.o"

# External object files for target server_vowelizer
server_vowelizer_EXTERNAL_OBJECTS =

server_vowelizer: CMakeFiles/server_vowelizer.dir/server.c.o
server_vowelizer: CMakeFiles/server_vowelizer.dir/transmission.c.o
server_vowelizer: CMakeFiles/server_vowelizer.dir/command_handler.c.o
server_vowelizer: CMakeFiles/server_vowelizer.dir/build.make
server_vowelizer: CMakeFiles/server_vowelizer.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/c/Workspace/Chegg/2022/redesigned-parakeet-vowelizer/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking C executable server_vowelizer"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/server_vowelizer.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/server_vowelizer.dir/build: server_vowelizer

.PHONY : CMakeFiles/server_vowelizer.dir/build

CMakeFiles/server_vowelizer.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/server_vowelizer.dir/cmake_clean.cmake
.PHONY : CMakeFiles/server_vowelizer.dir/clean

CMakeFiles/server_vowelizer.dir/depend:
	cd /mnt/c/Workspace/Chegg/2022/redesigned-parakeet-vowelizer/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/c/Workspace/Chegg/2022/redesigned-parakeet-vowelizer /mnt/c/Workspace/Chegg/2022/redesigned-parakeet-vowelizer /mnt/c/Workspace/Chegg/2022/redesigned-parakeet-vowelizer/cmake-build-debug /mnt/c/Workspace/Chegg/2022/redesigned-parakeet-vowelizer/cmake-build-debug /mnt/c/Workspace/Chegg/2022/redesigned-parakeet-vowelizer/cmake-build-debug/CMakeFiles/server_vowelizer.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/server_vowelizer.dir/depend

