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
CMAKE_SOURCE_DIR = /Users/youngwookkang/Documents/Berkeley/now/184/water-simulation/f2

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/youngwookkang/Documents/Berkeley/now/184/water-simulation/f2/build

# Include any dependencies generated for this target.
include deps/glfw/tests/CMakeFiles/reopen.dir/depend.make

# Include the progress variables for this target.
include deps/glfw/tests/CMakeFiles/reopen.dir/progress.make

# Include the compile flags for this target's objects.
include deps/glfw/tests/CMakeFiles/reopen.dir/flags.make

deps/glfw/tests/CMakeFiles/reopen.dir/reopen.c.o: deps/glfw/tests/CMakeFiles/reopen.dir/flags.make
deps/glfw/tests/CMakeFiles/reopen.dir/reopen.c.o: ../deps/glfw/tests/reopen.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/youngwookkang/Documents/Berkeley/now/184/water-simulation/f2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object deps/glfw/tests/CMakeFiles/reopen.dir/reopen.c.o"
	cd /Users/youngwookkang/Documents/Berkeley/now/184/water-simulation/f2/build/deps/glfw/tests && /Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/reopen.dir/reopen.c.o   -c /Users/youngwookkang/Documents/Berkeley/now/184/water-simulation/f2/deps/glfw/tests/reopen.c

deps/glfw/tests/CMakeFiles/reopen.dir/reopen.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/reopen.dir/reopen.c.i"
	cd /Users/youngwookkang/Documents/Berkeley/now/184/water-simulation/f2/build/deps/glfw/tests && /Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/youngwookkang/Documents/Berkeley/now/184/water-simulation/f2/deps/glfw/tests/reopen.c > CMakeFiles/reopen.dir/reopen.c.i

deps/glfw/tests/CMakeFiles/reopen.dir/reopen.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/reopen.dir/reopen.c.s"
	cd /Users/youngwookkang/Documents/Berkeley/now/184/water-simulation/f2/build/deps/glfw/tests && /Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/youngwookkang/Documents/Berkeley/now/184/water-simulation/f2/deps/glfw/tests/reopen.c -o CMakeFiles/reopen.dir/reopen.c.s

deps/glfw/tests/CMakeFiles/reopen.dir/reopen.c.o.requires:

.PHONY : deps/glfw/tests/CMakeFiles/reopen.dir/reopen.c.o.requires

deps/glfw/tests/CMakeFiles/reopen.dir/reopen.c.o.provides: deps/glfw/tests/CMakeFiles/reopen.dir/reopen.c.o.requires
	$(MAKE) -f deps/glfw/tests/CMakeFiles/reopen.dir/build.make deps/glfw/tests/CMakeFiles/reopen.dir/reopen.c.o.provides.build
.PHONY : deps/glfw/tests/CMakeFiles/reopen.dir/reopen.c.o.provides

deps/glfw/tests/CMakeFiles/reopen.dir/reopen.c.o.provides.build: deps/glfw/tests/CMakeFiles/reopen.dir/reopen.c.o


deps/glfw/tests/CMakeFiles/reopen.dir/__/deps/glad.c.o: deps/glfw/tests/CMakeFiles/reopen.dir/flags.make
deps/glfw/tests/CMakeFiles/reopen.dir/__/deps/glad.c.o: ../deps/glfw/deps/glad.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/youngwookkang/Documents/Berkeley/now/184/water-simulation/f2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object deps/glfw/tests/CMakeFiles/reopen.dir/__/deps/glad.c.o"
	cd /Users/youngwookkang/Documents/Berkeley/now/184/water-simulation/f2/build/deps/glfw/tests && /Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/reopen.dir/__/deps/glad.c.o   -c /Users/youngwookkang/Documents/Berkeley/now/184/water-simulation/f2/deps/glfw/deps/glad.c

deps/glfw/tests/CMakeFiles/reopen.dir/__/deps/glad.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/reopen.dir/__/deps/glad.c.i"
	cd /Users/youngwookkang/Documents/Berkeley/now/184/water-simulation/f2/build/deps/glfw/tests && /Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/youngwookkang/Documents/Berkeley/now/184/water-simulation/f2/deps/glfw/deps/glad.c > CMakeFiles/reopen.dir/__/deps/glad.c.i

deps/glfw/tests/CMakeFiles/reopen.dir/__/deps/glad.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/reopen.dir/__/deps/glad.c.s"
	cd /Users/youngwookkang/Documents/Berkeley/now/184/water-simulation/f2/build/deps/glfw/tests && /Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/youngwookkang/Documents/Berkeley/now/184/water-simulation/f2/deps/glfw/deps/glad.c -o CMakeFiles/reopen.dir/__/deps/glad.c.s

deps/glfw/tests/CMakeFiles/reopen.dir/__/deps/glad.c.o.requires:

.PHONY : deps/glfw/tests/CMakeFiles/reopen.dir/__/deps/glad.c.o.requires

deps/glfw/tests/CMakeFiles/reopen.dir/__/deps/glad.c.o.provides: deps/glfw/tests/CMakeFiles/reopen.dir/__/deps/glad.c.o.requires
	$(MAKE) -f deps/glfw/tests/CMakeFiles/reopen.dir/build.make deps/glfw/tests/CMakeFiles/reopen.dir/__/deps/glad.c.o.provides.build
.PHONY : deps/glfw/tests/CMakeFiles/reopen.dir/__/deps/glad.c.o.provides

deps/glfw/tests/CMakeFiles/reopen.dir/__/deps/glad.c.o.provides.build: deps/glfw/tests/CMakeFiles/reopen.dir/__/deps/glad.c.o


# Object files for target reopen
reopen_OBJECTS = \
"CMakeFiles/reopen.dir/reopen.c.o" \
"CMakeFiles/reopen.dir/__/deps/glad.c.o"

# External object files for target reopen
reopen_EXTERNAL_OBJECTS =

deps/glfw/tests/reopen: deps/glfw/tests/CMakeFiles/reopen.dir/reopen.c.o
deps/glfw/tests/reopen: deps/glfw/tests/CMakeFiles/reopen.dir/__/deps/glad.c.o
deps/glfw/tests/reopen: deps/glfw/tests/CMakeFiles/reopen.dir/build.make
deps/glfw/tests/reopen: deps/glfw/src/libglfw3.a
deps/glfw/tests/reopen: deps/glfw/tests/CMakeFiles/reopen.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/youngwookkang/Documents/Berkeley/now/184/water-simulation/f2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable reopen"
	cd /Users/youngwookkang/Documents/Berkeley/now/184/water-simulation/f2/build/deps/glfw/tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/reopen.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
deps/glfw/tests/CMakeFiles/reopen.dir/build: deps/glfw/tests/reopen

.PHONY : deps/glfw/tests/CMakeFiles/reopen.dir/build

deps/glfw/tests/CMakeFiles/reopen.dir/requires: deps/glfw/tests/CMakeFiles/reopen.dir/reopen.c.o.requires
deps/glfw/tests/CMakeFiles/reopen.dir/requires: deps/glfw/tests/CMakeFiles/reopen.dir/__/deps/glad.c.o.requires

.PHONY : deps/glfw/tests/CMakeFiles/reopen.dir/requires

deps/glfw/tests/CMakeFiles/reopen.dir/clean:
	cd /Users/youngwookkang/Documents/Berkeley/now/184/water-simulation/f2/build/deps/glfw/tests && $(CMAKE_COMMAND) -P CMakeFiles/reopen.dir/cmake_clean.cmake
.PHONY : deps/glfw/tests/CMakeFiles/reopen.dir/clean

deps/glfw/tests/CMakeFiles/reopen.dir/depend:
	cd /Users/youngwookkang/Documents/Berkeley/now/184/water-simulation/f2/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/youngwookkang/Documents/Berkeley/now/184/water-simulation/f2 /Users/youngwookkang/Documents/Berkeley/now/184/water-simulation/f2/deps/glfw/tests /Users/youngwookkang/Documents/Berkeley/now/184/water-simulation/f2/build /Users/youngwookkang/Documents/Berkeley/now/184/water-simulation/f2/build/deps/glfw/tests /Users/youngwookkang/Documents/Berkeley/now/184/water-simulation/f2/build/deps/glfw/tests/CMakeFiles/reopen.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : deps/glfw/tests/CMakeFiles/reopen.dir/depend

