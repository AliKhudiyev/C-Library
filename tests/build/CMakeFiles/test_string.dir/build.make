# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.18

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Disable VCS-based implicit rules.
% : %,v


# Disable VCS-based implicit rules.
% : RCS/%


# Disable VCS-based implicit rules.
% : RCS/%,v


# Disable VCS-based implicit rules.
% : SCCS/s.%


# Disable VCS-based implicit rules.
% : s.%


.SUFFIXES: .hpux_make_needs_suffix_list


# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.18.0/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.18.0/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/alikhudiyev/Desktop/Projects/C-Library/tests

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/alikhudiyev/Desktop/Projects/C-Library/tests/build

# Include any dependencies generated for this target.
include CMakeFiles/test_string.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/test_string.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/test_string.dir/flags.make

CMakeFiles/test_string.dir/test_string.c.o: CMakeFiles/test_string.dir/flags.make
CMakeFiles/test_string.dir/test_string.c.o: ../test_string.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/alikhudiyev/Desktop/Projects/C-Library/tests/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/test_string.dir/test_string.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/test_string.dir/test_string.c.o -c /Users/alikhudiyev/Desktop/Projects/C-Library/tests/test_string.c

CMakeFiles/test_string.dir/test_string.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/test_string.dir/test_string.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/alikhudiyev/Desktop/Projects/C-Library/tests/test_string.c > CMakeFiles/test_string.dir/test_string.c.i

CMakeFiles/test_string.dir/test_string.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/test_string.dir/test_string.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/alikhudiyev/Desktop/Projects/C-Library/tests/test_string.c -o CMakeFiles/test_string.dir/test_string.c.s

CMakeFiles/test_string.dir/Users/alikhudiyev/Desktop/Projects/C-Library/src/cpair.c.o: CMakeFiles/test_string.dir/flags.make
CMakeFiles/test_string.dir/Users/alikhudiyev/Desktop/Projects/C-Library/src/cpair.c.o: /Users/alikhudiyev/Desktop/Projects/C-Library/src/cpair.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/alikhudiyev/Desktop/Projects/C-Library/tests/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/test_string.dir/Users/alikhudiyev/Desktop/Projects/C-Library/src/cpair.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/test_string.dir/Users/alikhudiyev/Desktop/Projects/C-Library/src/cpair.c.o -c /Users/alikhudiyev/Desktop/Projects/C-Library/src/cpair.c

CMakeFiles/test_string.dir/Users/alikhudiyev/Desktop/Projects/C-Library/src/cpair.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/test_string.dir/Users/alikhudiyev/Desktop/Projects/C-Library/src/cpair.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/alikhudiyev/Desktop/Projects/C-Library/src/cpair.c > CMakeFiles/test_string.dir/Users/alikhudiyev/Desktop/Projects/C-Library/src/cpair.c.i

CMakeFiles/test_string.dir/Users/alikhudiyev/Desktop/Projects/C-Library/src/cpair.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/test_string.dir/Users/alikhudiyev/Desktop/Projects/C-Library/src/cpair.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/alikhudiyev/Desktop/Projects/C-Library/src/cpair.c -o CMakeFiles/test_string.dir/Users/alikhudiyev/Desktop/Projects/C-Library/src/cpair.c.s

CMakeFiles/test_string.dir/Users/alikhudiyev/Desktop/Projects/C-Library/src/cset.c.o: CMakeFiles/test_string.dir/flags.make
CMakeFiles/test_string.dir/Users/alikhudiyev/Desktop/Projects/C-Library/src/cset.c.o: /Users/alikhudiyev/Desktop/Projects/C-Library/src/cset.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/alikhudiyev/Desktop/Projects/C-Library/tests/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/test_string.dir/Users/alikhudiyev/Desktop/Projects/C-Library/src/cset.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/test_string.dir/Users/alikhudiyev/Desktop/Projects/C-Library/src/cset.c.o -c /Users/alikhudiyev/Desktop/Projects/C-Library/src/cset.c

CMakeFiles/test_string.dir/Users/alikhudiyev/Desktop/Projects/C-Library/src/cset.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/test_string.dir/Users/alikhudiyev/Desktop/Projects/C-Library/src/cset.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/alikhudiyev/Desktop/Projects/C-Library/src/cset.c > CMakeFiles/test_string.dir/Users/alikhudiyev/Desktop/Projects/C-Library/src/cset.c.i

CMakeFiles/test_string.dir/Users/alikhudiyev/Desktop/Projects/C-Library/src/cset.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/test_string.dir/Users/alikhudiyev/Desktop/Projects/C-Library/src/cset.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/alikhudiyev/Desktop/Projects/C-Library/src/cset.c -o CMakeFiles/test_string.dir/Users/alikhudiyev/Desktop/Projects/C-Library/src/cset.c.s

CMakeFiles/test_string.dir/Users/alikhudiyev/Desktop/Projects/C-Library/src/cstring.c.o: CMakeFiles/test_string.dir/flags.make
CMakeFiles/test_string.dir/Users/alikhudiyev/Desktop/Projects/C-Library/src/cstring.c.o: /Users/alikhudiyev/Desktop/Projects/C-Library/src/cstring.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/alikhudiyev/Desktop/Projects/C-Library/tests/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/test_string.dir/Users/alikhudiyev/Desktop/Projects/C-Library/src/cstring.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/test_string.dir/Users/alikhudiyev/Desktop/Projects/C-Library/src/cstring.c.o -c /Users/alikhudiyev/Desktop/Projects/C-Library/src/cstring.c

CMakeFiles/test_string.dir/Users/alikhudiyev/Desktop/Projects/C-Library/src/cstring.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/test_string.dir/Users/alikhudiyev/Desktop/Projects/C-Library/src/cstring.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/alikhudiyev/Desktop/Projects/C-Library/src/cstring.c > CMakeFiles/test_string.dir/Users/alikhudiyev/Desktop/Projects/C-Library/src/cstring.c.i

CMakeFiles/test_string.dir/Users/alikhudiyev/Desktop/Projects/C-Library/src/cstring.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/test_string.dir/Users/alikhudiyev/Desktop/Projects/C-Library/src/cstring.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/alikhudiyev/Desktop/Projects/C-Library/src/cstring.c -o CMakeFiles/test_string.dir/Users/alikhudiyev/Desktop/Projects/C-Library/src/cstring.c.s

CMakeFiles/test_string.dir/Users/alikhudiyev/Desktop/Projects/C-Library/src/cvector.c.o: CMakeFiles/test_string.dir/flags.make
CMakeFiles/test_string.dir/Users/alikhudiyev/Desktop/Projects/C-Library/src/cvector.c.o: /Users/alikhudiyev/Desktop/Projects/C-Library/src/cvector.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/alikhudiyev/Desktop/Projects/C-Library/tests/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/test_string.dir/Users/alikhudiyev/Desktop/Projects/C-Library/src/cvector.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/test_string.dir/Users/alikhudiyev/Desktop/Projects/C-Library/src/cvector.c.o -c /Users/alikhudiyev/Desktop/Projects/C-Library/src/cvector.c

CMakeFiles/test_string.dir/Users/alikhudiyev/Desktop/Projects/C-Library/src/cvector.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/test_string.dir/Users/alikhudiyev/Desktop/Projects/C-Library/src/cvector.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/alikhudiyev/Desktop/Projects/C-Library/src/cvector.c > CMakeFiles/test_string.dir/Users/alikhudiyev/Desktop/Projects/C-Library/src/cvector.c.i

CMakeFiles/test_string.dir/Users/alikhudiyev/Desktop/Projects/C-Library/src/cvector.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/test_string.dir/Users/alikhudiyev/Desktop/Projects/C-Library/src/cvector.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/alikhudiyev/Desktop/Projects/C-Library/src/cvector.c -o CMakeFiles/test_string.dir/Users/alikhudiyev/Desktop/Projects/C-Library/src/cvector.c.s

# Object files for target test_string
test_string_OBJECTS = \
"CMakeFiles/test_string.dir/test_string.c.o" \
"CMakeFiles/test_string.dir/Users/alikhudiyev/Desktop/Projects/C-Library/src/cpair.c.o" \
"CMakeFiles/test_string.dir/Users/alikhudiyev/Desktop/Projects/C-Library/src/cset.c.o" \
"CMakeFiles/test_string.dir/Users/alikhudiyev/Desktop/Projects/C-Library/src/cstring.c.o" \
"CMakeFiles/test_string.dir/Users/alikhudiyev/Desktop/Projects/C-Library/src/cvector.c.o"

# External object files for target test_string
test_string_EXTERNAL_OBJECTS =

test_string: CMakeFiles/test_string.dir/test_string.c.o
test_string: CMakeFiles/test_string.dir/Users/alikhudiyev/Desktop/Projects/C-Library/src/cpair.c.o
test_string: CMakeFiles/test_string.dir/Users/alikhudiyev/Desktop/Projects/C-Library/src/cset.c.o
test_string: CMakeFiles/test_string.dir/Users/alikhudiyev/Desktop/Projects/C-Library/src/cstring.c.o
test_string: CMakeFiles/test_string.dir/Users/alikhudiyev/Desktop/Projects/C-Library/src/cvector.c.o
test_string: CMakeFiles/test_string.dir/build.make
test_string: CMakeFiles/test_string.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/alikhudiyev/Desktop/Projects/C-Library/tests/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking C executable test_string"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test_string.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/test_string.dir/build: test_string

.PHONY : CMakeFiles/test_string.dir/build

CMakeFiles/test_string.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/test_string.dir/cmake_clean.cmake
.PHONY : CMakeFiles/test_string.dir/clean

CMakeFiles/test_string.dir/depend:
	cd /Users/alikhudiyev/Desktop/Projects/C-Library/tests/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/alikhudiyev/Desktop/Projects/C-Library/tests /Users/alikhudiyev/Desktop/Projects/C-Library/tests /Users/alikhudiyev/Desktop/Projects/C-Library/tests/build /Users/alikhudiyev/Desktop/Projects/C-Library/tests/build /Users/alikhudiyev/Desktop/Projects/C-Library/tests/build/CMakeFiles/test_string.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/test_string.dir/depend
