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
CMAKE_SOURCE_DIR = /Users/youngwookkang/Documents/Berkeley/now/184/water-simulation/f2

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/youngwookkang/Documents/Berkeley/now/184/water-simulation/f2/cmake-build-debug

# Include any dependencies generated for this target.
include deps/glfw/examples/CMakeFiles/wave.dir/depend.make

# Include the progress variables for this target.
include deps/glfw/examples/CMakeFiles/wave.dir/progress.make

# Include the compile flags for this target's objects.
include deps/glfw/examples/CMakeFiles/wave.dir/flags.make

deps/glfw/examples/wave.app/Contents/Resources/glfw.icns: ../deps/glfw/examples/glfw.icns
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Copying OS X content deps/glfw/examples/wave.app/Contents/Resources/glfw.icns"
	$(CMAKE_COMMAND) -E copy /Users/youngwookkang/Documents/Berkeley/now/184/water-simulation/f2/deps/glfw/examples/glfw.icns deps/glfw/examples/wave.app/Contents/Resources/glfw.icns

deps/glfw/examples/CMakeFiles/wave.dir/wave.c.o: deps/glfw/examples/CMakeFiles/wave.dir/flags.make
deps/glfw/examples/CMakeFiles/wave.dir/wave.c.o: ../deps/glfw/examples/wave.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/youngwookkang/Documents/Berkeley/now/184/water-simulation/f2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object deps/glfw/examples/CMakeFiles/wave.dir/wave.c.o"
	cd /Users/youngwookkang/Documents/Berkeley/now/184/water-simulation/f2/cmake-build-debug/deps/glfw/examples && /Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/wave.dir/wave.c.o   -c /Users/youngwookkang/Documents/Berkeley/now/184/water-simulation/f2/deps/glfw/examples/wave.c

deps/glfw/examples/CMakeFiles/wave.dir/wave.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/wave.dir/wave.c.i"
	cd /Users/youngwookkang/Documents/Berkeley/now/184/water-simulation/f2/cmake-build-debug/deps/glfw/examples && /Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/youngwookkang/Documents/Berkeley/now/184/water-simulation/f2/deps/glfw/examples/wave.c > CMakeFiles/wave.dir/wave.c.i

deps/glfw/examples/CMakeFiles/wave.dir/wave.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/wave.dir/wave.c.s"
	cd /Users/youngwookkang/Documents/Berkeley/now/184/water-simulation/f2/cmake-build-debug/deps/glfw/examples && /Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/youngwookkang/Documents/Berkeley/now/184/water-simulation/f2/deps/glfw/examples/wave.c -o CMakeFiles/wave.dir/wave.c.s

deps/glfw/examples/CMakeFiles/wave.dir/wave.c.o.requires:

.PHONY : deps/glfw/examples/CMakeFiles/wave.dir/wave.c.o.requires

deps/glfw/examples/CMakeFiles/wave.dir/wave.c.o.provides: deps/glfw/examples/CMakeFiles/wave.dir/wave.c.o.requires
	$(MAKE) -f deps/glfw/examples/CMakeFiles/wave.dir/build.make deps/glfw/examples/CMakeFiles/wave.dir/wave.c.o.provides.build
.PHONY : deps/glfw/examples/CMakeFiles/wave.dir/wave.c.o.provides

deps/glfw/examples/CMakeFiles/wave.dir/wave.c.o.provides.build: deps/glfw/examples/CMakeFiles/wave.dir/wave.c.o


deps/glfw/examples/CMakeFiles/wave.dir/__/deps/glad.c.o: deps/glfw/examples/CMakeFiles/wave.dir/flags.make
deps/glfw/examples/CMakeFiles/wave.dir/__/deps/glad.c.o: ../deps/glfw/deps/glad.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/youngwookkang/Documents/Berkeley/now/184/water-simulation/f2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object deps/glfw/examples/CMakeFiles/wave.dir/__/deps/glad.c.o"
	cd /Users/youngwookkang/Documents/Berkeley/now/184/water-simulation/f2/cmake-build-debug/deps/glfw/examples && /Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/wave.dir/__/deps/glad.c.o   -c /Users/youngwookkang/Documents/Berkeley/now/184/water-simulation/f2/deps/glfw/deps/glad.c

deps/glfw/examples/CMakeFiles/wave.dir/__/deps/glad.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/wave.dir/__/deps/glad.c.i"
	cd /Users/youngwookkang/Documents/Berkeley/now/184/water-simulation/f2/cmake-build-debug/deps/glfw/examples && /Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/youngwookkang/Documents/Berkeley/now/184/water-simulation/f2/deps/glfw/deps/glad.c > CMakeFiles/wave.dir/__/deps/glad.c.i

deps/glfw/examples/CMakeFiles/wave.dir/__/deps/glad.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/wave.dir/__/deps/glad.c.s"
	cd /Users/youngwookkang/Documents/Berkeley/now/184/water-simulation/f2/cmake-build-debug/deps/glfw/examples && /Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/youngwookkang/Documents/Berkeley/now/184/water-simulation/f2/deps/glfw/deps/glad.c -o CMakeFiles/wave.dir/__/deps/glad.c.s

deps/glfw/examples/CMakeFiles/wave.dir/__/deps/glad.c.o.requires:

.PHONY : deps/glfw/examples/CMakeFiles/wave.dir/__/deps/glad.c.o.requires

deps/glfw/examples/CMakeFiles/wave.dir/__/deps/glad.c.o.provides: deps/glfw/examples/CMakeFiles/wave.dir/__/deps/glad.c.o.requires
	$(MAKE) -f deps/glfw/examples/CMakeFiles/wave.dir/build.make deps/glfw/examples/CMakeFiles/wave.dir/__/deps/glad.c.o.provides.build
.PHONY : deps/glfw/examples/CMakeFiles/wave.dir/__/deps/glad.c.o.provides

deps/glfw/examples/CMakeFiles/wave.dir/__/deps/glad.c.o.provides.build: deps/glfw/examples/CMakeFiles/wave.dir/__/deps/glad.c.o


# Object files for target wave
wave_OBJECTS = \
"CMakeFiles/wave.dir/wave.c.o" \
"CMakeFiles/wave.dir/__/deps/glad.c.o"

# External object files for target wave
wave_EXTERNAL_OBJECTS =

deps/glfw/examples/wave.app/Contents/MacOS/wave: deps/glfw/examples/CMakeFiles/wave.dir/wave.c.o
deps/glfw/examples/wave.app/Contents/MacOS/wave: deps/glfw/examples/CMakeFiles/wave.dir/__/deps/glad.c.o
deps/glfw/examples/wave.app/Contents/MacOS/wave: deps/glfw/examples/CMakeFiles/wave.dir/build.make
deps/glfw/examples/wave.app/Contents/MacOS/wave: deps/glfw/src/libglfw3.a
deps/glfw/examples/wave.app/Contents/MacOS/wave: deps/glfw/examples/CMakeFiles/wave.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/youngwookkang/Documents/Berkeley/now/184/water-simulation/f2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable wave.app/Contents/MacOS/wave"
	cd /Users/youngwookkang/Documents/Berkeley/now/184/water-simulation/f2/cmake-build-debug/deps/glfw/examples && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/wave.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
deps/glfw/examples/CMakeFiles/wave.dir/build: deps/glfw/examples/wave.app/Contents/MacOS/wave
deps/glfw/examples/CMakeFiles/wave.dir/build: deps/glfw/examples/wave.app/Contents/Resources/glfw.icns

.PHONY : deps/glfw/examples/CMakeFiles/wave.dir/build

deps/glfw/examples/CMakeFiles/wave.dir/requires: deps/glfw/examples/CMakeFiles/wave.dir/wave.c.o.requires
deps/glfw/examples/CMakeFiles/wave.dir/requires: deps/glfw/examples/CMakeFiles/wave.dir/__/deps/glad.c.o.requires

.PHONY : deps/glfw/examples/CMakeFiles/wave.dir/requires

deps/glfw/examples/CMakeFiles/wave.dir/clean:
	cd /Users/youngwookkang/Documents/Berkeley/now/184/water-simulation/f2/cmake-build-debug/deps/glfw/examples && $(CMAKE_COMMAND) -P CMakeFiles/wave.dir/cmake_clean.cmake
.PHONY : deps/glfw/examples/CMakeFiles/wave.dir/clean

deps/glfw/examples/CMakeFiles/wave.dir/depend:
	cd /Users/youngwookkang/Documents/Berkeley/now/184/water-simulation/f2/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/youngwookkang/Documents/Berkeley/now/184/water-simulation/f2 /Users/youngwookkang/Documents/Berkeley/now/184/water-simulation/f2/deps/glfw/examples /Users/youngwookkang/Documents/Berkeley/now/184/water-simulation/f2/cmake-build-debug /Users/youngwookkang/Documents/Berkeley/now/184/water-simulation/f2/cmake-build-debug/deps/glfw/examples /Users/youngwookkang/Documents/Berkeley/now/184/water-simulation/f2/cmake-build-debug/deps/glfw/examples/CMakeFiles/wave.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : deps/glfw/examples/CMakeFiles/wave.dir/depend

