# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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
CMAKE_SOURCE_DIR = /home/robot/posetrack/posecart/unit_test

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/robot/posetrack/posecart/unit_test

# Include any dependencies generated for this target.
include CMakeFiles/test_posecartprocess.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/test_posecartprocess.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/test_posecartprocess.dir/flags.make

CMakeFiles/test_posecartprocess.dir/test_posecartprocess.cpp.o: CMakeFiles/test_posecartprocess.dir/flags.make
CMakeFiles/test_posecartprocess.dir/test_posecartprocess.cpp.o: test_posecartprocess.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/robot/posetrack/posecart/unit_test/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/test_posecartprocess.dir/test_posecartprocess.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/test_posecartprocess.dir/test_posecartprocess.cpp.o -c /home/robot/posetrack/posecart/unit_test/test_posecartprocess.cpp

CMakeFiles/test_posecartprocess.dir/test_posecartprocess.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test_posecartprocess.dir/test_posecartprocess.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/robot/posetrack/posecart/unit_test/test_posecartprocess.cpp > CMakeFiles/test_posecartprocess.dir/test_posecartprocess.cpp.i

CMakeFiles/test_posecartprocess.dir/test_posecartprocess.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test_posecartprocess.dir/test_posecartprocess.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/robot/posetrack/posecart/unit_test/test_posecartprocess.cpp -o CMakeFiles/test_posecartprocess.dir/test_posecartprocess.cpp.s

CMakeFiles/test_posecartprocess.dir/test_posecartprocess.cpp.o.requires:
.PHONY : CMakeFiles/test_posecartprocess.dir/test_posecartprocess.cpp.o.requires

CMakeFiles/test_posecartprocess.dir/test_posecartprocess.cpp.o.provides: CMakeFiles/test_posecartprocess.dir/test_posecartprocess.cpp.o.requires
	$(MAKE) -f CMakeFiles/test_posecartprocess.dir/build.make CMakeFiles/test_posecartprocess.dir/test_posecartprocess.cpp.o.provides.build
.PHONY : CMakeFiles/test_posecartprocess.dir/test_posecartprocess.cpp.o.provides

CMakeFiles/test_posecartprocess.dir/test_posecartprocess.cpp.o.provides.build: CMakeFiles/test_posecartprocess.dir/test_posecartprocess.cpp.o

# Object files for target test_posecartprocess
test_posecartprocess_OBJECTS = \
"CMakeFiles/test_posecartprocess.dir/test_posecartprocess.cpp.o"

# External object files for target test_posecartprocess
test_posecartprocess_EXTERNAL_OBJECTS =

test_posecartprocess: CMakeFiles/test_posecartprocess.dir/test_posecartprocess.cpp.o
test_posecartprocess: CMakeFiles/test_posecartprocess.dir/build.make
test_posecartprocess: /usr/lib/libgtest.a
test_posecartprocess: libposecartprocess.a
test_posecartprocess: CMakeFiles/test_posecartprocess.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable test_posecartprocess"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test_posecartprocess.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/test_posecartprocess.dir/build: test_posecartprocess
.PHONY : CMakeFiles/test_posecartprocess.dir/build

CMakeFiles/test_posecartprocess.dir/requires: CMakeFiles/test_posecartprocess.dir/test_posecartprocess.cpp.o.requires
.PHONY : CMakeFiles/test_posecartprocess.dir/requires

CMakeFiles/test_posecartprocess.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/test_posecartprocess.dir/cmake_clean.cmake
.PHONY : CMakeFiles/test_posecartprocess.dir/clean

CMakeFiles/test_posecartprocess.dir/depend:
	cd /home/robot/posetrack/posecart/unit_test && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/robot/posetrack/posecart/unit_test /home/robot/posetrack/posecart/unit_test /home/robot/posetrack/posecart/unit_test /home/robot/posetrack/posecart/unit_test /home/robot/posetrack/posecart/unit_test/CMakeFiles/test_posecartprocess.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/test_posecartprocess.dir/depend

