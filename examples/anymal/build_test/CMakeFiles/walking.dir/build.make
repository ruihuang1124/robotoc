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
CMAKE_SOURCE_DIR = /home/katayama/src/idocp/examples/anymal

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/katayama/src/idocp/examples/anymal/build_test

# Include any dependencies generated for this target.
include CMakeFiles/walking.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/walking.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/walking.dir/flags.make

CMakeFiles/walking.dir/walking.cpp.o: CMakeFiles/walking.dir/flags.make
CMakeFiles/walking.dir/walking.cpp.o: ../walking.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/katayama/src/idocp/examples/anymal/build_test/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/walking.dir/walking.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/walking.dir/walking.cpp.o -c /home/katayama/src/idocp/examples/anymal/walking.cpp

CMakeFiles/walking.dir/walking.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/walking.dir/walking.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/katayama/src/idocp/examples/anymal/walking.cpp > CMakeFiles/walking.dir/walking.cpp.i

CMakeFiles/walking.dir/walking.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/walking.dir/walking.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/katayama/src/idocp/examples/anymal/walking.cpp -o CMakeFiles/walking.dir/walking.cpp.s

# Object files for target walking
walking_OBJECTS = \
"CMakeFiles/walking.dir/walking.cpp.o"

# External object files for target walking
walking_EXTERNAL_OBJECTS =

walking: CMakeFiles/walking.dir/walking.cpp.o
walking: CMakeFiles/walking.dir/build.make
walking: /home/katayama/install-idocp-test/lib/libidocp.so
walking: /opt/openrobots/lib/libpinocchio.so
walking: /usr/lib/x86_64-linux-gnu/libboost_filesystem.so
walking: /usr/lib/x86_64-linux-gnu/libboost_serialization.so
walking: /usr/lib/x86_64-linux-gnu/libboost_system.so
walking: CMakeFiles/walking.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/katayama/src/idocp/examples/anymal/build_test/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable walking"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/walking.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/walking.dir/build: walking

.PHONY : CMakeFiles/walking.dir/build

CMakeFiles/walking.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/walking.dir/cmake_clean.cmake
.PHONY : CMakeFiles/walking.dir/clean

CMakeFiles/walking.dir/depend:
	cd /home/katayama/src/idocp/examples/anymal/build_test && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/katayama/src/idocp/examples/anymal /home/katayama/src/idocp/examples/anymal /home/katayama/src/idocp/examples/anymal/build_test /home/katayama/src/idocp/examples/anymal/build_test /home/katayama/src/idocp/examples/anymal/build_test/CMakeFiles/walking.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/walking.dir/depend

