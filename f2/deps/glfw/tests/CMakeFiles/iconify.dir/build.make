# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.10.2/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.10.2/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/youngwookkang/Documents/Berkeley/now/184/f2/deps/glfw

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/youngwookkang/Documents/Berkeley/now/184/f2/deps/glfw

# Include any dependencies generated for this target.
include tests/CMakeFiles/iconify.dir/depend.make

# Include the progress variables for this target.
include tests/CMakeFiles/iconify.dir/progress.make

# Include the compile flags for this target's objects.
include tests/CMakeFiles/iconify.dir/flags.make

tests/CMakeFiles/iconify.dir/iconify.c.o: tests/CMakeFiles/iconify.dir/flags.make
tests/CMakeFiles/iconify.dir/iconify.c.o: tests/iconify.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/youngwookkang/Documents/Berkeley/now/184/f2/deps/glfw/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object tests/CMakeFiles/iconify.dir/iconify.c.o"
	cd /Users/youngwookkang/Documents/Berkeley/now/184/f2/deps/glfw/tests && /Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/iconify.dir/iconify.c.o   -c /Users/youngwookkang/Documents/Berkeley/now/184/f2/deps/glfw/tests/iconify.c

tests/CMakeFiles/iconify.dir/iconify.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/iconify.dir/iconify.c.i"
	cd /Users/youngwookkang/Documents/Berkeley/now/184/f2/deps/glfw/tests && /Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/youngwookkang/Documents/Berkeley/now/184/f2/deps/glfw/tests/iconify.c > CMakeFiles/iconify.dir/iconify.c.i

tests/CMakeFiles/iconify.dir/iconify.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/iconify.dir/iconify.c.s"
	cd /Users/youngwookkang/Documents/Berkeley/now/184/f2/deps/glfw/tests && /Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/youngwookkang/Documents/Berkeley/now/184/f2/deps/glfw/tests/iconify.c -o CMakeFiles/iconify.dir/iconify.c.s

tests/CMakeFiles/iconify.dir/iconify.c.o.requires:

.PHONY : tests/CMakeFiles/iconify.dir/iconify.c.o.requires

tests/CMakeFiles/iconify.dir/iconify.c.o.provides: tests/CMakeFiles/iconify.dir/iconify.c.o.requires
	$(MAKE) -f tests/CMakeFiles/iconify.dir/build.make tests/CMakeFiles/iconify.dir/iconify.c.o.provides.build
.PHONY : tests/CMakeFiles/iconify.dir/iconify.c.o.provides

tests/CMakeFiles/iconify.dir/iconify.c.o.provides.build: tests/CMakeFiles/iconify.dir/iconify.c.o


tests/CMakeFiles/iconify.dir/__/deps/getopt.c.o: tests/CMakeFiles/iconify.dir/flags.make
tests/CMakeFiles/iconify.dir/__/deps/getopt.c.o: deps/getopt.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/youngwookkang/Documents/Berkeley/now/184/f2/deps/glfw/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object tests/CMakeFiles/iconify.dir/__/deps/getopt.c.o"
	cd /Users/youngwookkang/Documents/Berkeley/now/184/f2/deps/glfw/tests && /Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/iconify.dir/__/deps/getopt.c.o   -c /Users/youngwookkang/Documents/Berkeley/now/184/f2/deps/glfw/deps/getopt.c

tests/CMakeFiles/iconify.dir/__/deps/getopt.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/iconify.dir/__/deps/getopt.c.i"
	cd /Users/youngwookkang/Documents/Berkeley/now/184/f2/deps/glfw/tests && /Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/youngwookkang/Documents/Berkeley/now/184/f2/deps/glfw/deps/getopt.c > CMakeFiles/iconify.dir/__/deps/getopt.c.i

tests/CMakeFiles/iconify.dir/__/deps/getopt.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/iconify.dir/__/deps/getopt.c.s"
	cd /Users/youngwookkang/Documents/Berkeley/now/184/f2/deps/glfw/tests && /Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/youngwookkang/Documents/Berkeley/now/184/f2/deps/glfw/deps/getopt.c -o CMakeFiles/iconify.dir/__/deps/getopt.c.s

tests/CMakeFiles/iconify.dir/__/deps/getopt.c.o.requires:

.PHONY : tests/CMakeFiles/iconify.dir/__/deps/getopt.c.o.requires

tests/CMakeFiles/iconify.dir/__/deps/getopt.c.o.provides: tests/CMakeFiles/iconify.dir/__/deps/getopt.c.o.requires
	$(MAKE) -f tests/CMakeFiles/iconify.dir/build.make tests/CMakeFiles/iconify.dir/__/deps/getopt.c.o.provides.build
.PHONY : tests/CMakeFiles/iconify.dir/__/deps/getopt.c.o.provides

tests/CMakeFiles/iconify.dir/__/deps/getopt.c.o.provides.build: tests/CMakeFiles/iconify.dir/__/deps/getopt.c.o


tests/CMakeFiles/iconify.dir/__/deps/glad.c.o: tests/CMakeFiles/iconify.dir/flags.make
tests/CMakeFiles/iconify.dir/__/deps/glad.c.o: deps/glad.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/youngwookkang/Documents/Berkeley/now/184/f2/deps/glfw/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object tests/CMakeFiles/iconify.dir/__/deps/glad.c.o"
	cd /Users/youngwookkang/Documents/Berkeley/now/184/f2/deps/glfw/tests && /Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/iconify.dir/__/deps/glad.c.o   -c /Users/youngwookkang/Documents/Berkeley/now/184/f2/deps/glfw/deps/glad.c

tests/CMakeFiles/iconify.dir/__/deps/glad.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/iconify.dir/__/deps/glad.c.i"
	cd /Users/youngwookkang/Documents/Berkeley/now/184/f2/deps/glfw/tests && /Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/youngwookkang/Documents/Berkeley/now/184/f2/deps/glfw/deps/glad.c > CMakeFiles/iconify.dir/__/deps/glad.c.i

tests/CMakeFiles/iconify.dir/__/deps/glad.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/iconify.dir/__/deps/glad.c.s"
	cd /Users/youngwookkang/Documents/Berkeley/now/184/f2/deps/glfw/tests && /Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/youngwookkang/Documents/Berkeley/now/184/f2/deps/glfw/deps/glad.c -o CMakeFiles/iconify.dir/__/deps/glad.c.s

tests/CMakeFiles/iconify.dir/__/deps/glad.c.o.requires:

.PHONY : tests/CMakeFiles/iconify.dir/__/deps/glad.c.o.requires

tests/CMakeFiles/iconify.dir/__/deps/glad.c.o.provides: tests/CMakeFiles/iconify.dir/__/deps/glad.c.o.requires
	$(MAKE) -f tests/CMakeFiles/iconify.dir/build.make tests/CMakeFiles/iconify.dir/__/deps/glad.c.o.provides.build
.PHONY : tests/CMakeFiles/iconify.dir/__/deps/glad.c.o.provides

tests/CMakeFiles/iconify.dir/__/deps/glad.c.o.provides.build: tests/CMakeFiles/iconify.dir/__/deps/glad.c.o


# Object files for target iconify
iconify_OBJECTS = \
"CMakeFiles/iconify.dir/iconify.c.o" \
"CMakeFiles/iconify.dir/__/deps/getopt.c.o" \
"CMakeFiles/iconify.dir/__/deps/glad.c.o"

# External object files for target iconify
iconify_EXTERNAL_OBJECTS =

tests/iconify: tests/CMakeFiles/iconify.dir/iconify.c.o
tests/iconify: tests/CMakeFiles/iconify.dir/__/deps/getopt.c.o
tests/iconify: tests/CMakeFiles/iconify.dir/__/deps/glad.c.o
tests/iconify: tests/CMakeFiles/iconify.dir/build.make
tests/iconify: src/libglfw3.a
tests/iconify: tests/CMakeFiles/iconify.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/youngwookkang/Documents/Berkeley/now/184/f2/deps/glfw/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking C executable iconify"
	cd /Users/youngwookkang/Documents/Berkeley/now/184/f2/deps/glfw/tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/iconify.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tests/CMakeFiles/iconify.dir/build: tests/iconify

.PHONY : tests/CMakeFiles/iconify.dir/build

tests/CMakeFiles/iconify.dir/requires: tests/CMakeFiles/iconify.dir/iconify.c.o.requires
tests/CMakeFiles/iconify.dir/requires: tests/CMakeFiles/iconify.dir/__/deps/getopt.c.o.requires
tests/CMakeFiles/iconify.dir/requires: tests/CMakeFiles/iconify.dir/__/deps/glad.c.o.requires

.PHONY : tests/CMakeFiles/iconify.dir/requires

tests/CMakeFiles/iconify.dir/clean:
	cd /Users/youngwookkang/Documents/Berkeley/now/184/f2/deps/glfw/tests && $(CMAKE_COMMAND) -P CMakeFiles/iconify.dir/cmake_clean.cmake
.PHONY : tests/CMakeFiles/iconify.dir/clean

tests/CMakeFiles/iconify.dir/depend:
	cd /Users/youngwookkang/Documents/Berkeley/now/184/f2/deps/glfw && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/youngwookkang/Documents/Berkeley/now/184/f2/deps/glfw /Users/youngwookkang/Documents/Berkeley/now/184/f2/deps/glfw/tests /Users/youngwookkang/Documents/Berkeley/now/184/f2/deps/glfw /Users/youngwookkang/Documents/Berkeley/now/184/f2/deps/glfw/tests /Users/youngwookkang/Documents/Berkeley/now/184/f2/deps/glfw/tests/CMakeFiles/iconify.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : tests/CMakeFiles/iconify.dir/depend

