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
include deps/glm/glm/CMakeFiles/glm_dummy.dir/depend.make

# Include the progress variables for this target.
include deps/glm/glm/CMakeFiles/glm_dummy.dir/progress.make

# Include the compile flags for this target's objects.
include deps/glm/glm/CMakeFiles/glm_dummy.dir/flags.make

deps/glm/glm/CMakeFiles/glm_dummy.dir/detail/dummy.cpp.o: deps/glm/glm/CMakeFiles/glm_dummy.dir/flags.make
deps/glm/glm/CMakeFiles/glm_dummy.dir/detail/dummy.cpp.o: ../deps/glm/glm/detail/dummy.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/youngwookkang/Documents/Berkeley/now/184/water-simulation/f2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object deps/glm/glm/CMakeFiles/glm_dummy.dir/detail/dummy.cpp.o"
	cd /Users/youngwookkang/Documents/Berkeley/now/184/water-simulation/f2/build/deps/glm/glm && /Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/glm_dummy.dir/detail/dummy.cpp.o -c /Users/youngwookkang/Documents/Berkeley/now/184/water-simulation/f2/deps/glm/glm/detail/dummy.cpp

deps/glm/glm/CMakeFiles/glm_dummy.dir/detail/dummy.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/glm_dummy.dir/detail/dummy.cpp.i"
	cd /Users/youngwookkang/Documents/Berkeley/now/184/water-simulation/f2/build/deps/glm/glm && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/youngwookkang/Documents/Berkeley/now/184/water-simulation/f2/deps/glm/glm/detail/dummy.cpp > CMakeFiles/glm_dummy.dir/detail/dummy.cpp.i

deps/glm/glm/CMakeFiles/glm_dummy.dir/detail/dummy.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/glm_dummy.dir/detail/dummy.cpp.s"
	cd /Users/youngwookkang/Documents/Berkeley/now/184/water-simulation/f2/build/deps/glm/glm && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/youngwookkang/Documents/Berkeley/now/184/water-simulation/f2/deps/glm/glm/detail/dummy.cpp -o CMakeFiles/glm_dummy.dir/detail/dummy.cpp.s

deps/glm/glm/CMakeFiles/glm_dummy.dir/detail/dummy.cpp.o.requires:

.PHONY : deps/glm/glm/CMakeFiles/glm_dummy.dir/detail/dummy.cpp.o.requires

deps/glm/glm/CMakeFiles/glm_dummy.dir/detail/dummy.cpp.o.provides: deps/glm/glm/CMakeFiles/glm_dummy.dir/detail/dummy.cpp.o.requires
	$(MAKE) -f deps/glm/glm/CMakeFiles/glm_dummy.dir/build.make deps/glm/glm/CMakeFiles/glm_dummy.dir/detail/dummy.cpp.o.provides.build
.PHONY : deps/glm/glm/CMakeFiles/glm_dummy.dir/detail/dummy.cpp.o.provides

deps/glm/glm/CMakeFiles/glm_dummy.dir/detail/dummy.cpp.o.provides.build: deps/glm/glm/CMakeFiles/glm_dummy.dir/detail/dummy.cpp.o


deps/glm/glm/CMakeFiles/glm_dummy.dir/detail/glm.cpp.o: deps/glm/glm/CMakeFiles/glm_dummy.dir/flags.make
deps/glm/glm/CMakeFiles/glm_dummy.dir/detail/glm.cpp.o: ../deps/glm/glm/detail/glm.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/youngwookkang/Documents/Berkeley/now/184/water-simulation/f2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object deps/glm/glm/CMakeFiles/glm_dummy.dir/detail/glm.cpp.o"
	cd /Users/youngwookkang/Documents/Berkeley/now/184/water-simulation/f2/build/deps/glm/glm && /Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/glm_dummy.dir/detail/glm.cpp.o -c /Users/youngwookkang/Documents/Berkeley/now/184/water-simulation/f2/deps/glm/glm/detail/glm.cpp

deps/glm/glm/CMakeFiles/glm_dummy.dir/detail/glm.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/glm_dummy.dir/detail/glm.cpp.i"
	cd /Users/youngwookkang/Documents/Berkeley/now/184/water-simulation/f2/build/deps/glm/glm && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/youngwookkang/Documents/Berkeley/now/184/water-simulation/f2/deps/glm/glm/detail/glm.cpp > CMakeFiles/glm_dummy.dir/detail/glm.cpp.i

deps/glm/glm/CMakeFiles/glm_dummy.dir/detail/glm.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/glm_dummy.dir/detail/glm.cpp.s"
	cd /Users/youngwookkang/Documents/Berkeley/now/184/water-simulation/f2/build/deps/glm/glm && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/youngwookkang/Documents/Berkeley/now/184/water-simulation/f2/deps/glm/glm/detail/glm.cpp -o CMakeFiles/glm_dummy.dir/detail/glm.cpp.s

deps/glm/glm/CMakeFiles/glm_dummy.dir/detail/glm.cpp.o.requires:

.PHONY : deps/glm/glm/CMakeFiles/glm_dummy.dir/detail/glm.cpp.o.requires

deps/glm/glm/CMakeFiles/glm_dummy.dir/detail/glm.cpp.o.provides: deps/glm/glm/CMakeFiles/glm_dummy.dir/detail/glm.cpp.o.requires
	$(MAKE) -f deps/glm/glm/CMakeFiles/glm_dummy.dir/build.make deps/glm/glm/CMakeFiles/glm_dummy.dir/detail/glm.cpp.o.provides.build
.PHONY : deps/glm/glm/CMakeFiles/glm_dummy.dir/detail/glm.cpp.o.provides

deps/glm/glm/CMakeFiles/glm_dummy.dir/detail/glm.cpp.o.provides.build: deps/glm/glm/CMakeFiles/glm_dummy.dir/detail/glm.cpp.o


# Object files for target glm_dummy
glm_dummy_OBJECTS = \
"CMakeFiles/glm_dummy.dir/detail/dummy.cpp.o" \
"CMakeFiles/glm_dummy.dir/detail/glm.cpp.o"

# External object files for target glm_dummy
glm_dummy_EXTERNAL_OBJECTS =

deps/glm/glm/glm_dummy: deps/glm/glm/CMakeFiles/glm_dummy.dir/detail/dummy.cpp.o
deps/glm/glm/glm_dummy: deps/glm/glm/CMakeFiles/glm_dummy.dir/detail/glm.cpp.o
deps/glm/glm/glm_dummy: deps/glm/glm/CMakeFiles/glm_dummy.dir/build.make
deps/glm/glm/glm_dummy: deps/glm/glm/CMakeFiles/glm_dummy.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/youngwookkang/Documents/Berkeley/now/184/water-simulation/f2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable glm_dummy"
	cd /Users/youngwookkang/Documents/Berkeley/now/184/water-simulation/f2/build/deps/glm/glm && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/glm_dummy.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
deps/glm/glm/CMakeFiles/glm_dummy.dir/build: deps/glm/glm/glm_dummy

.PHONY : deps/glm/glm/CMakeFiles/glm_dummy.dir/build

deps/glm/glm/CMakeFiles/glm_dummy.dir/requires: deps/glm/glm/CMakeFiles/glm_dummy.dir/detail/dummy.cpp.o.requires
deps/glm/glm/CMakeFiles/glm_dummy.dir/requires: deps/glm/glm/CMakeFiles/glm_dummy.dir/detail/glm.cpp.o.requires

.PHONY : deps/glm/glm/CMakeFiles/glm_dummy.dir/requires

deps/glm/glm/CMakeFiles/glm_dummy.dir/clean:
	cd /Users/youngwookkang/Documents/Berkeley/now/184/water-simulation/f2/build/deps/glm/glm && $(CMAKE_COMMAND) -P CMakeFiles/glm_dummy.dir/cmake_clean.cmake
.PHONY : deps/glm/glm/CMakeFiles/glm_dummy.dir/clean

deps/glm/glm/CMakeFiles/glm_dummy.dir/depend:
	cd /Users/youngwookkang/Documents/Berkeley/now/184/water-simulation/f2/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/youngwookkang/Documents/Berkeley/now/184/water-simulation/f2 /Users/youngwookkang/Documents/Berkeley/now/184/water-simulation/f2/deps/glm/glm /Users/youngwookkang/Documents/Berkeley/now/184/water-simulation/f2/build /Users/youngwookkang/Documents/Berkeley/now/184/water-simulation/f2/build/deps/glm/glm /Users/youngwookkang/Documents/Berkeley/now/184/water-simulation/f2/build/deps/glm/glm/CMakeFiles/glm_dummy.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : deps/glm/glm/CMakeFiles/glm_dummy.dir/depend
