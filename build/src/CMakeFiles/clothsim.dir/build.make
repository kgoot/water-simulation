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
CMAKE_SOURCE_DIR = /Users/karina/cs184/water-simulation

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/karina/cs184/water-simulation/build

# Include any dependencies generated for this target.
include src/CMakeFiles/clothsim.dir/depend.make

# Include the progress variables for this target.
include src/CMakeFiles/clothsim.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/clothsim.dir/flags.make

src/CMakeFiles/clothsim.dir/water.cpp.o: src/CMakeFiles/clothsim.dir/flags.make
src/CMakeFiles/clothsim.dir/water.cpp.o: ../src/water.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/karina/cs184/water-simulation/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/CMakeFiles/clothsim.dir/water.cpp.o"
	cd /Users/karina/cs184/water-simulation/build/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/clothsim.dir/water.cpp.o -c /Users/karina/cs184/water-simulation/src/water.cpp

src/CMakeFiles/clothsim.dir/water.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/clothsim.dir/water.cpp.i"
	cd /Users/karina/cs184/water-simulation/build/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/karina/cs184/water-simulation/src/water.cpp > CMakeFiles/clothsim.dir/water.cpp.i

src/CMakeFiles/clothsim.dir/water.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/clothsim.dir/water.cpp.s"
	cd /Users/karina/cs184/water-simulation/build/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/karina/cs184/water-simulation/src/water.cpp -o CMakeFiles/clothsim.dir/water.cpp.s

src/CMakeFiles/clothsim.dir/water.cpp.o.requires:

.PHONY : src/CMakeFiles/clothsim.dir/water.cpp.o.requires

src/CMakeFiles/clothsim.dir/water.cpp.o.provides: src/CMakeFiles/clothsim.dir/water.cpp.o.requires
	$(MAKE) -f src/CMakeFiles/clothsim.dir/build.make src/CMakeFiles/clothsim.dir/water.cpp.o.provides.build
.PHONY : src/CMakeFiles/clothsim.dir/water.cpp.o.provides

src/CMakeFiles/clothsim.dir/water.cpp.o.provides.build: src/CMakeFiles/clothsim.dir/water.cpp.o


src/CMakeFiles/clothsim.dir/clothMesh.cpp.o: src/CMakeFiles/clothsim.dir/flags.make
src/CMakeFiles/clothsim.dir/clothMesh.cpp.o: ../src/clothMesh.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/karina/cs184/water-simulation/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object src/CMakeFiles/clothsim.dir/clothMesh.cpp.o"
	cd /Users/karina/cs184/water-simulation/build/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/clothsim.dir/clothMesh.cpp.o -c /Users/karina/cs184/water-simulation/src/clothMesh.cpp

src/CMakeFiles/clothsim.dir/clothMesh.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/clothsim.dir/clothMesh.cpp.i"
	cd /Users/karina/cs184/water-simulation/build/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/karina/cs184/water-simulation/src/clothMesh.cpp > CMakeFiles/clothsim.dir/clothMesh.cpp.i

src/CMakeFiles/clothsim.dir/clothMesh.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/clothsim.dir/clothMesh.cpp.s"
	cd /Users/karina/cs184/water-simulation/build/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/karina/cs184/water-simulation/src/clothMesh.cpp -o CMakeFiles/clothsim.dir/clothMesh.cpp.s

src/CMakeFiles/clothsim.dir/clothMesh.cpp.o.requires:

.PHONY : src/CMakeFiles/clothsim.dir/clothMesh.cpp.o.requires

src/CMakeFiles/clothsim.dir/clothMesh.cpp.o.provides: src/CMakeFiles/clothsim.dir/clothMesh.cpp.o.requires
	$(MAKE) -f src/CMakeFiles/clothsim.dir/build.make src/CMakeFiles/clothsim.dir/clothMesh.cpp.o.provides.build
.PHONY : src/CMakeFiles/clothsim.dir/clothMesh.cpp.o.provides

src/CMakeFiles/clothsim.dir/clothMesh.cpp.o.provides.build: src/CMakeFiles/clothsim.dir/clothMesh.cpp.o


src/CMakeFiles/clothsim.dir/collision/sphere.cpp.o: src/CMakeFiles/clothsim.dir/flags.make
src/CMakeFiles/clothsim.dir/collision/sphere.cpp.o: ../src/collision/sphere.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/karina/cs184/water-simulation/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object src/CMakeFiles/clothsim.dir/collision/sphere.cpp.o"
	cd /Users/karina/cs184/water-simulation/build/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/clothsim.dir/collision/sphere.cpp.o -c /Users/karina/cs184/water-simulation/src/collision/sphere.cpp

src/CMakeFiles/clothsim.dir/collision/sphere.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/clothsim.dir/collision/sphere.cpp.i"
	cd /Users/karina/cs184/water-simulation/build/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/karina/cs184/water-simulation/src/collision/sphere.cpp > CMakeFiles/clothsim.dir/collision/sphere.cpp.i

src/CMakeFiles/clothsim.dir/collision/sphere.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/clothsim.dir/collision/sphere.cpp.s"
	cd /Users/karina/cs184/water-simulation/build/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/karina/cs184/water-simulation/src/collision/sphere.cpp -o CMakeFiles/clothsim.dir/collision/sphere.cpp.s

src/CMakeFiles/clothsim.dir/collision/sphere.cpp.o.requires:

.PHONY : src/CMakeFiles/clothsim.dir/collision/sphere.cpp.o.requires

src/CMakeFiles/clothsim.dir/collision/sphere.cpp.o.provides: src/CMakeFiles/clothsim.dir/collision/sphere.cpp.o.requires
	$(MAKE) -f src/CMakeFiles/clothsim.dir/build.make src/CMakeFiles/clothsim.dir/collision/sphere.cpp.o.provides.build
.PHONY : src/CMakeFiles/clothsim.dir/collision/sphere.cpp.o.provides

src/CMakeFiles/clothsim.dir/collision/sphere.cpp.o.provides.build: src/CMakeFiles/clothsim.dir/collision/sphere.cpp.o


src/CMakeFiles/clothsim.dir/collision/plane.cpp.o: src/CMakeFiles/clothsim.dir/flags.make
src/CMakeFiles/clothsim.dir/collision/plane.cpp.o: ../src/collision/plane.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/karina/cs184/water-simulation/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object src/CMakeFiles/clothsim.dir/collision/plane.cpp.o"
	cd /Users/karina/cs184/water-simulation/build/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/clothsim.dir/collision/plane.cpp.o -c /Users/karina/cs184/water-simulation/src/collision/plane.cpp

src/CMakeFiles/clothsim.dir/collision/plane.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/clothsim.dir/collision/plane.cpp.i"
	cd /Users/karina/cs184/water-simulation/build/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/karina/cs184/water-simulation/src/collision/plane.cpp > CMakeFiles/clothsim.dir/collision/plane.cpp.i

src/CMakeFiles/clothsim.dir/collision/plane.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/clothsim.dir/collision/plane.cpp.s"
	cd /Users/karina/cs184/water-simulation/build/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/karina/cs184/water-simulation/src/collision/plane.cpp -o CMakeFiles/clothsim.dir/collision/plane.cpp.s

src/CMakeFiles/clothsim.dir/collision/plane.cpp.o.requires:

.PHONY : src/CMakeFiles/clothsim.dir/collision/plane.cpp.o.requires

src/CMakeFiles/clothsim.dir/collision/plane.cpp.o.provides: src/CMakeFiles/clothsim.dir/collision/plane.cpp.o.requires
	$(MAKE) -f src/CMakeFiles/clothsim.dir/build.make src/CMakeFiles/clothsim.dir/collision/plane.cpp.o.provides.build
.PHONY : src/CMakeFiles/clothsim.dir/collision/plane.cpp.o.provides

src/CMakeFiles/clothsim.dir/collision/plane.cpp.o.provides.build: src/CMakeFiles/clothsim.dir/collision/plane.cpp.o


src/CMakeFiles/clothsim.dir/main.cpp.o: src/CMakeFiles/clothsim.dir/flags.make
src/CMakeFiles/clothsim.dir/main.cpp.o: ../src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/karina/cs184/water-simulation/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object src/CMakeFiles/clothsim.dir/main.cpp.o"
	cd /Users/karina/cs184/water-simulation/build/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/clothsim.dir/main.cpp.o -c /Users/karina/cs184/water-simulation/src/main.cpp

src/CMakeFiles/clothsim.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/clothsim.dir/main.cpp.i"
	cd /Users/karina/cs184/water-simulation/build/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/karina/cs184/water-simulation/src/main.cpp > CMakeFiles/clothsim.dir/main.cpp.i

src/CMakeFiles/clothsim.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/clothsim.dir/main.cpp.s"
	cd /Users/karina/cs184/water-simulation/build/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/karina/cs184/water-simulation/src/main.cpp -o CMakeFiles/clothsim.dir/main.cpp.s

src/CMakeFiles/clothsim.dir/main.cpp.o.requires:

.PHONY : src/CMakeFiles/clothsim.dir/main.cpp.o.requires

src/CMakeFiles/clothsim.dir/main.cpp.o.provides: src/CMakeFiles/clothsim.dir/main.cpp.o.requires
	$(MAKE) -f src/CMakeFiles/clothsim.dir/build.make src/CMakeFiles/clothsim.dir/main.cpp.o.provides.build
.PHONY : src/CMakeFiles/clothsim.dir/main.cpp.o.provides

src/CMakeFiles/clothsim.dir/main.cpp.o.provides.build: src/CMakeFiles/clothsim.dir/main.cpp.o


src/CMakeFiles/clothsim.dir/waterSimulator.cpp.o: src/CMakeFiles/clothsim.dir/flags.make
src/CMakeFiles/clothsim.dir/waterSimulator.cpp.o: ../src/waterSimulator.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/karina/cs184/water-simulation/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object src/CMakeFiles/clothsim.dir/waterSimulator.cpp.o"
	cd /Users/karina/cs184/water-simulation/build/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/clothsim.dir/waterSimulator.cpp.o -c /Users/karina/cs184/water-simulation/src/waterSimulator.cpp

src/CMakeFiles/clothsim.dir/waterSimulator.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/clothsim.dir/waterSimulator.cpp.i"
	cd /Users/karina/cs184/water-simulation/build/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/karina/cs184/water-simulation/src/waterSimulator.cpp > CMakeFiles/clothsim.dir/waterSimulator.cpp.i

src/CMakeFiles/clothsim.dir/waterSimulator.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/clothsim.dir/waterSimulator.cpp.s"
	cd /Users/karina/cs184/water-simulation/build/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/karina/cs184/water-simulation/src/waterSimulator.cpp -o CMakeFiles/clothsim.dir/waterSimulator.cpp.s

src/CMakeFiles/clothsim.dir/waterSimulator.cpp.o.requires:

.PHONY : src/CMakeFiles/clothsim.dir/waterSimulator.cpp.o.requires

src/CMakeFiles/clothsim.dir/waterSimulator.cpp.o.provides: src/CMakeFiles/clothsim.dir/waterSimulator.cpp.o.requires
	$(MAKE) -f src/CMakeFiles/clothsim.dir/build.make src/CMakeFiles/clothsim.dir/waterSimulator.cpp.o.provides.build
.PHONY : src/CMakeFiles/clothsim.dir/waterSimulator.cpp.o.provides

src/CMakeFiles/clothsim.dir/waterSimulator.cpp.o.provides.build: src/CMakeFiles/clothsim.dir/waterSimulator.cpp.o


src/CMakeFiles/clothsim.dir/misc/sphere_drawing.cpp.o: src/CMakeFiles/clothsim.dir/flags.make
src/CMakeFiles/clothsim.dir/misc/sphere_drawing.cpp.o: ../src/misc/sphere_drawing.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/karina/cs184/water-simulation/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object src/CMakeFiles/clothsim.dir/misc/sphere_drawing.cpp.o"
	cd /Users/karina/cs184/water-simulation/build/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/clothsim.dir/misc/sphere_drawing.cpp.o -c /Users/karina/cs184/water-simulation/src/misc/sphere_drawing.cpp

src/CMakeFiles/clothsim.dir/misc/sphere_drawing.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/clothsim.dir/misc/sphere_drawing.cpp.i"
	cd /Users/karina/cs184/water-simulation/build/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/karina/cs184/water-simulation/src/misc/sphere_drawing.cpp > CMakeFiles/clothsim.dir/misc/sphere_drawing.cpp.i

src/CMakeFiles/clothsim.dir/misc/sphere_drawing.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/clothsim.dir/misc/sphere_drawing.cpp.s"
	cd /Users/karina/cs184/water-simulation/build/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/karina/cs184/water-simulation/src/misc/sphere_drawing.cpp -o CMakeFiles/clothsim.dir/misc/sphere_drawing.cpp.s

src/CMakeFiles/clothsim.dir/misc/sphere_drawing.cpp.o.requires:

.PHONY : src/CMakeFiles/clothsim.dir/misc/sphere_drawing.cpp.o.requires

src/CMakeFiles/clothsim.dir/misc/sphere_drawing.cpp.o.provides: src/CMakeFiles/clothsim.dir/misc/sphere_drawing.cpp.o.requires
	$(MAKE) -f src/CMakeFiles/clothsim.dir/build.make src/CMakeFiles/clothsim.dir/misc/sphere_drawing.cpp.o.provides.build
.PHONY : src/CMakeFiles/clothsim.dir/misc/sphere_drawing.cpp.o.provides

src/CMakeFiles/clothsim.dir/misc/sphere_drawing.cpp.o.provides.build: src/CMakeFiles/clothsim.dir/misc/sphere_drawing.cpp.o


src/CMakeFiles/clothsim.dir/camera.cpp.o: src/CMakeFiles/clothsim.dir/flags.make
src/CMakeFiles/clothsim.dir/camera.cpp.o: ../src/camera.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/karina/cs184/water-simulation/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object src/CMakeFiles/clothsim.dir/camera.cpp.o"
	cd /Users/karina/cs184/water-simulation/build/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/clothsim.dir/camera.cpp.o -c /Users/karina/cs184/water-simulation/src/camera.cpp

src/CMakeFiles/clothsim.dir/camera.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/clothsim.dir/camera.cpp.i"
	cd /Users/karina/cs184/water-simulation/build/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/karina/cs184/water-simulation/src/camera.cpp > CMakeFiles/clothsim.dir/camera.cpp.i

src/CMakeFiles/clothsim.dir/camera.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/clothsim.dir/camera.cpp.s"
	cd /Users/karina/cs184/water-simulation/build/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/karina/cs184/water-simulation/src/camera.cpp -o CMakeFiles/clothsim.dir/camera.cpp.s

src/CMakeFiles/clothsim.dir/camera.cpp.o.requires:

.PHONY : src/CMakeFiles/clothsim.dir/camera.cpp.o.requires

src/CMakeFiles/clothsim.dir/camera.cpp.o.provides: src/CMakeFiles/clothsim.dir/camera.cpp.o.requires
	$(MAKE) -f src/CMakeFiles/clothsim.dir/build.make src/CMakeFiles/clothsim.dir/camera.cpp.o.provides.build
.PHONY : src/CMakeFiles/clothsim.dir/camera.cpp.o.provides

src/CMakeFiles/clothsim.dir/camera.cpp.o.provides.build: src/CMakeFiles/clothsim.dir/camera.cpp.o


src/CMakeFiles/clothsim.dir/container.cpp.o: src/CMakeFiles/clothsim.dir/flags.make
src/CMakeFiles/clothsim.dir/container.cpp.o: ../src/container.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/karina/cs184/water-simulation/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object src/CMakeFiles/clothsim.dir/container.cpp.o"
	cd /Users/karina/cs184/water-simulation/build/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/clothsim.dir/container.cpp.o -c /Users/karina/cs184/water-simulation/src/container.cpp

src/CMakeFiles/clothsim.dir/container.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/clothsim.dir/container.cpp.i"
	cd /Users/karina/cs184/water-simulation/build/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/karina/cs184/water-simulation/src/container.cpp > CMakeFiles/clothsim.dir/container.cpp.i

src/CMakeFiles/clothsim.dir/container.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/clothsim.dir/container.cpp.s"
	cd /Users/karina/cs184/water-simulation/build/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/karina/cs184/water-simulation/src/container.cpp -o CMakeFiles/clothsim.dir/container.cpp.s

src/CMakeFiles/clothsim.dir/container.cpp.o.requires:

.PHONY : src/CMakeFiles/clothsim.dir/container.cpp.o.requires

src/CMakeFiles/clothsim.dir/container.cpp.o.provides: src/CMakeFiles/clothsim.dir/container.cpp.o.requires
	$(MAKE) -f src/CMakeFiles/clothsim.dir/build.make src/CMakeFiles/clothsim.dir/container.cpp.o.provides.build
.PHONY : src/CMakeFiles/clothsim.dir/container.cpp.o.provides

src/CMakeFiles/clothsim.dir/container.cpp.o.provides.build: src/CMakeFiles/clothsim.dir/container.cpp.o


# Object files for target clothsim
clothsim_OBJECTS = \
"CMakeFiles/clothsim.dir/water.cpp.o" \
"CMakeFiles/clothsim.dir/clothMesh.cpp.o" \
"CMakeFiles/clothsim.dir/collision/sphere.cpp.o" \
"CMakeFiles/clothsim.dir/collision/plane.cpp.o" \
"CMakeFiles/clothsim.dir/main.cpp.o" \
"CMakeFiles/clothsim.dir/waterSimulator.cpp.o" \
"CMakeFiles/clothsim.dir/misc/sphere_drawing.cpp.o" \
"CMakeFiles/clothsim.dir/camera.cpp.o" \
"CMakeFiles/clothsim.dir/container.cpp.o"

# External object files for target clothsim
clothsim_EXTERNAL_OBJECTS =

clothsim: src/CMakeFiles/clothsim.dir/water.cpp.o
clothsim: src/CMakeFiles/clothsim.dir/clothMesh.cpp.o
clothsim: src/CMakeFiles/clothsim.dir/collision/sphere.cpp.o
clothsim: src/CMakeFiles/clothsim.dir/collision/plane.cpp.o
clothsim: src/CMakeFiles/clothsim.dir/main.cpp.o
clothsim: src/CMakeFiles/clothsim.dir/waterSimulator.cpp.o
clothsim: src/CMakeFiles/clothsim.dir/misc/sphere_drawing.cpp.o
clothsim: src/CMakeFiles/clothsim.dir/camera.cpp.o
clothsim: src/CMakeFiles/clothsim.dir/container.cpp.o
clothsim: src/CMakeFiles/clothsim.dir/build.make
clothsim: CGL/src/libCGL.a
clothsim: ext/nanogui/libnanogui.dylib
clothsim: /usr/local/lib/libfreetype.dylib
clothsim: src/CMakeFiles/clothsim.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/karina/cs184/water-simulation/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Linking CXX executable ../clothsim"
	cd /Users/karina/cs184/water-simulation/build/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/clothsim.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/clothsim.dir/build: clothsim

.PHONY : src/CMakeFiles/clothsim.dir/build

src/CMakeFiles/clothsim.dir/requires: src/CMakeFiles/clothsim.dir/water.cpp.o.requires
src/CMakeFiles/clothsim.dir/requires: src/CMakeFiles/clothsim.dir/clothMesh.cpp.o.requires
src/CMakeFiles/clothsim.dir/requires: src/CMakeFiles/clothsim.dir/collision/sphere.cpp.o.requires
src/CMakeFiles/clothsim.dir/requires: src/CMakeFiles/clothsim.dir/collision/plane.cpp.o.requires
src/CMakeFiles/clothsim.dir/requires: src/CMakeFiles/clothsim.dir/main.cpp.o.requires
src/CMakeFiles/clothsim.dir/requires: src/CMakeFiles/clothsim.dir/waterSimulator.cpp.o.requires
src/CMakeFiles/clothsim.dir/requires: src/CMakeFiles/clothsim.dir/misc/sphere_drawing.cpp.o.requires
src/CMakeFiles/clothsim.dir/requires: src/CMakeFiles/clothsim.dir/camera.cpp.o.requires
src/CMakeFiles/clothsim.dir/requires: src/CMakeFiles/clothsim.dir/container.cpp.o.requires

.PHONY : src/CMakeFiles/clothsim.dir/requires

src/CMakeFiles/clothsim.dir/clean:
	cd /Users/karina/cs184/water-simulation/build/src && $(CMAKE_COMMAND) -P CMakeFiles/clothsim.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/clothsim.dir/clean

src/CMakeFiles/clothsim.dir/depend:
	cd /Users/karina/cs184/water-simulation/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/karina/cs184/water-simulation /Users/karina/cs184/water-simulation/src /Users/karina/cs184/water-simulation/build /Users/karina/cs184/water-simulation/build/src /Users/karina/cs184/water-simulation/build/src/CMakeFiles/clothsim.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/clothsim.dir/depend

