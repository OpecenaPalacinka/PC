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
CMAKE_SOURCE_DIR = /mnt/d/PC/Cviceni7/parser

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/d/PC/Cviceni7/parser/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/parser.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/parser.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/parser.dir/flags.make

CMakeFiles/parser.dir/parser/operators.o: CMakeFiles/parser.dir/flags.make
CMakeFiles/parser.dir/parser/operators.o: ../parser/operators.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/d/PC/Cviceni7/parser/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/parser.dir/parser/operators.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/parser.dir/parser/operators.o   -c /mnt/d/PC/Cviceni7/parser/parser/operators.c

CMakeFiles/parser.dir/parser/operators.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/parser.dir/parser/operators.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/d/PC/Cviceni7/parser/parser/operators.c > CMakeFiles/parser.dir/parser/operators.i

CMakeFiles/parser.dir/parser/operators.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/parser.dir/parser/operators.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/d/PC/Cviceni7/parser/parser/operators.c -o CMakeFiles/parser.dir/parser/operators.s

CMakeFiles/parser.dir/parser/parser.o: CMakeFiles/parser.dir/flags.make
CMakeFiles/parser.dir/parser/parser.o: ../parser/parser.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/d/PC/Cviceni7/parser/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/parser.dir/parser/parser.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/parser.dir/parser/parser.o   -c /mnt/d/PC/Cviceni7/parser/parser/parser.c

CMakeFiles/parser.dir/parser/parser.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/parser.dir/parser/parser.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/d/PC/Cviceni7/parser/parser/parser.c > CMakeFiles/parser.dir/parser/parser.i

CMakeFiles/parser.dir/parser/parser.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/parser.dir/parser/parser.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/d/PC/Cviceni7/parser/parser/parser.c -o CMakeFiles/parser.dir/parser/parser.s

CMakeFiles/parser.dir/parser/stack.o: CMakeFiles/parser.dir/flags.make
CMakeFiles/parser.dir/parser/stack.o: ../parser/stack.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/d/PC/Cviceni7/parser/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/parser.dir/parser/stack.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/parser.dir/parser/stack.o   -c /mnt/d/PC/Cviceni7/parser/parser/stack.c

CMakeFiles/parser.dir/parser/stack.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/parser.dir/parser/stack.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/d/PC/Cviceni7/parser/parser/stack.c > CMakeFiles/parser.dir/parser/stack.i

CMakeFiles/parser.dir/parser/stack.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/parser.dir/parser/stack.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/d/PC/Cviceni7/parser/parser/stack.c -o CMakeFiles/parser.dir/parser/stack.s

# Object files for target parser
parser_OBJECTS = \
"CMakeFiles/parser.dir/parser/operators.o" \
"CMakeFiles/parser.dir/parser/parser.o" \
"CMakeFiles/parser.dir/parser/stack.o"

# External object files for target parser
parser_EXTERNAL_OBJECTS =

parser: CMakeFiles/parser.dir/parser/operators.o
parser: CMakeFiles/parser.dir/parser/parser.o
parser: CMakeFiles/parser.dir/parser/stack.o
parser: CMakeFiles/parser.dir/build.make
parser: CMakeFiles/parser.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/d/PC/Cviceni7/parser/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking C executable parser"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/parser.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/parser.dir/build: parser

.PHONY : CMakeFiles/parser.dir/build

CMakeFiles/parser.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/parser.dir/cmake_clean.cmake
.PHONY : CMakeFiles/parser.dir/clean

CMakeFiles/parser.dir/depend:
	cd /mnt/d/PC/Cviceni7/parser/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/d/PC/Cviceni7/parser /mnt/d/PC/Cviceni7/parser /mnt/d/PC/Cviceni7/parser/cmake-build-debug /mnt/d/PC/Cviceni7/parser/cmake-build-debug /mnt/d/PC/Cviceni7/parser/cmake-build-debug/CMakeFiles/parser.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/parser.dir/depend
