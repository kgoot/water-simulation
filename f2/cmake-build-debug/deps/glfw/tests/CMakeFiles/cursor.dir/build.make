# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.9

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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/anna/Desktop/final184/water-simulation/f2

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/anna/Desktop/final184/water-simulation/f2/cmake-build-debug

# Include any dependencies generated for this target.
include deps/glfw/tests/CMakeFiles/cursor.dir/depend.make

# Include the progress variables for this target.
include deps/glfw/tests/CMakeFiles/cursor.dir/progress.make

# Include the compile flags for this target's objects.
include deps/glfw/tests/CMakeFiles/cursor.dir/flags.make

deps/glfw/tests/CMakeFiles/cursor.dir/cursor.c.o: deps/glfw/tests/CMakeFiles/cursor.dir/flags.make
deps/glfw/tests/CMakeFiles/cursor.dir/cursor.c.o: ../deps/glfw/tests/cursor.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/anna/Desktop/final184/water-simulation/f2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object deps/glfw/tests/CMakeFiles/cursor.dir/cursor.c.o"
	cd /Users/anna/Desktop/final184/water-simulation/f2/cmake-build-debug/deps/glfw/tests && /Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/cursor.dir/cursor.c.o   -c /Users/anna/Desktop/final184/water-simulation/f2/deps/glfw/tests/cursor.c

deps/glfw/tests/CMakeFiles/cursor.dir/cursor.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/cursor.dir/cursor.c.i"
	cd /Users/anna/Desktop/final184/water-simulation/f2/cmake-build-debug/deps/glfw/tests && /Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/anna/Desktop/final184/water-simulation/f2/deps/glfw/tests/cursor.c > CMakeFiles/cursor.dir/cursor.c.i

deps/glfw/tests/CMakeFiles/cursor.dir/cursor.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/cursor.dir/cursor.c.s"
	cd /Users/anna/Desktop/final184/water-simulation/f2/cmake-build-debug/deps/glfw/tests && /Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/anna/Desktop/final184/water-simulation/f2/deps/glfw/tests/cursor.c -o CMakeFiles/cursor.dir/cursor.c.s

deps/glfw/tests/CMakeFiles/cursor.dir/cursor.c.o.requires:

.PHONY : deps/glfw/tests/CMakeFiles/cursor.dir/cursor.c.o.requires

deps/glfw/tests/CMakeFiles/cursor.dir/cursor.c.o.provides: deps/glfw/tests/CMakeFiles/cursor.dir/cursor.c.o.requires
	$(MAKE) -f deps/glfw/tests/CMakeFiles/cursor.dir/build.make deps/glfw/tests/CMakeFiles/cursor.dir/cursor.c.o.provides.build
.PHONY : deps/glfw/tests/CMakeFiles/cursor.dir/cursor.c.o.provides

deps/glfw/tests/CMakeFiles/cursor.dir/cursor.c.o.provides.build: deps/glfw/tests/CMakeFiles/cursor.dir/cursor.c.o


deps/glfw/tests/CMakeFiles/cursor.dir/__/deps/glad.c.o: deps/glfw/tests/CMakeFiles/cursor.dir/flags.make
deps/glfw/tests/CMakeFiles/cursor.dir/__/deps/glad.c.o: ../deps/glfw/deps/glad.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/anna/Desktop/final184/water-simulation/f2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object deps/glfw/tests/CMakeFiles/cursor.dir/__/deps/glad.c.o"
	cd /Users/anna/Desktop/final184/water-simulation/f2/cmake-build-debug/deps/glfw/tests && /Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/cursor.dir/__/deps/glad.c.o   -c /Users/anna/Desktop/final184/water-simulation/f2/deps/glfw/deps/glad.c

deps/glfw/tests/CMakeFiles/cursor.dir/__/deps/glad.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/cursor.dir/__/deps/glad.c.i"
	cd /Users/anna/Desktop/final184/water-simulation/f2/cmake-build-debug/deps/glfw/tests && /Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/anna/Desktop/final184/water-simulation/f2/deps/glfw/deps/glad.c > CMakeFiles/cursor.dir/__/deps/glad.c.i

deps/glfw/tests/CMakeFiles/cursor.dir/__/deps/glad.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/cursor.dir/__/deps/glad.c.s"
	cd /Users/anna/Desktop/final184/water-simulation/f2/cmake-build-debug/deps/glfw/tests && /Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/anna/Desktop/final184/water-simulation/f2/deps/glfw/deps/glad.c -o CMakeFiles/cursor.dir/__/deps/glad.c.s

deps/glfw/tests/CMakeFiles/cursor.dir/__/deps/glad.c.o.requires:

.PHONY : deps/glfw/tests/CMakeFiles/cursor.dir/__/deps/glad.c.o.requires

deps/glfw/tests/CMakeFiles/cursor.dir/__/deps/glad.c.o.provides: deps/glfw/tests/CMakeFiles/cursor.dir/__/deps/glad.c.o.requires
	$(MAKE) -f deps/glfw/tests/CMakeFiles/cursor.dir/build.make deps/glfw/tests/CMakeFiles/cursor.dir/__/deps/glad.c.o.provides.build
.PHONY : deps/glfw/tests/CMakeFiles/cursor.dir/__/deps/glad.c.o.provides

deps/glfw/tests/CMakeFiles/cursor.dir/__/deps/glad.c.o.provides.build: deps/glfw/tests/CMakeFiles/cursor.dir/__/deps/glad.c.o


# Object files for target cursor
cursor_OBJECTS = \
"CMakeFiles/cursor.dir/cursor.c.o" \
"CMakeFiles/cursor.dir/__/deps/glad.c.o"

# External object files for target cursor
cursor_EXTERNAL_OBJECTS =

deps/glfw/tests/cursor: deps/glfw/tests/CMakeFiles/cursor.dir/cursor.c.o
deps/glfw/tests/cursor: deps/glfw/tests/CMakeFiles/cursor.dir/__/deps/glad.c.o
deps/glfw/tests/cursor: deps/glfw/tests/CMakeFiles/cursor.dir/build.make
deps/glfw/tests/cursor: deps/glfw/src/libglfw3.a
deps/glfw/tests/cursor: deps/glfw/tests/CMakeFiles/cursor.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/anna/Desktop/final184/water-simulation/f2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable cursor"
	cd /Users/anna/Desktop/final184/water-simulation/f2/cmake-build-debug/deps/glfw/tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/cursor.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
deps/glfw/tests/CMakeFiles/cursor.dir/build: deps/glfw/tests/cursor

.PHONY : deps/glfw/tests/CMakeFiles/cursor.dir/build

deps/glfw/tests/CMakeFiles/cursor.dir/requires: deps/glfw/tests/CMakeFiles/cursor.dir/cursor.c.o.requires
deps/glfw/tests/CMakeFiles/cursor.dir/requires: deps/glfw/tests/CMakeFiles/cursor.dir/__/deps/glad.c.o.requires

.PHONY : deps/glfw/tests/CMakeFiles/cursor.dir/requires

deps/glfw/tests/CMakeFiles/cursor.dir/clean:
	cd /Users/anna/Desktop/final184/water-simulation/f2/cmake-build-debug/deps/glfw/tests && $(CMAKE_COMMAND) -P CMakeFiles/cursor.dir/cmake_clean.cmake
.PHONY : deps/glfw/tests/CMakeFiles/cursor.dir/clean

deps/glfw/tests/CMakeFiles/cursor.dir/depend:
	cd /Users/anna/Desktop/final184/water-simulation/f2/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/anna/Desktop/final184/water-simulation/f2 /Users/anna/Desktop/final184/water-simulation/f2/deps/glfw/tests /Users/anna/Desktop/final184/water-simulation/f2/cmake-build-debug /Users/anna/Desktop/final184/water-simulation/f2/cmake-build-debug/deps/glfw/tests /Users/anna/Desktop/final184/water-simulation/f2/cmake-build-debug/deps/glfw/tests/CMakeFiles/cursor.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : deps/glfw/tests/CMakeFiles/cursor.dir/depend

