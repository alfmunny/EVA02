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


# Produce verbose output by default.
VERBOSE = 1

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
CMAKE_SOURCE_DIR = /home/alfmunny/Projects/EVA02

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/alfmunny/Projects/EVA02

# Include any dependencies generated for this target.
include CMakeFiles/test_logging.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/test_logging.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/test_logging.dir/flags.make

CMakeFiles/test_logging.dir/test/test_logging.cpp.o: CMakeFiles/test_logging.dir/flags.make
CMakeFiles/test_logging.dir/test/test_logging.cpp.o: test/test_logging.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/alfmunny/Projects/EVA02/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/test_logging.dir/test/test_logging.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test_logging.dir/test/test_logging.cpp.o -c /home/alfmunny/Projects/EVA02/test/test_logging.cpp

CMakeFiles/test_logging.dir/test/test_logging.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test_logging.dir/test/test_logging.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/alfmunny/Projects/EVA02/test/test_logging.cpp > CMakeFiles/test_logging.dir/test/test_logging.cpp.i

CMakeFiles/test_logging.dir/test/test_logging.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test_logging.dir/test/test_logging.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/alfmunny/Projects/EVA02/test/test_logging.cpp -o CMakeFiles/test_logging.dir/test/test_logging.cpp.s

# Object files for target test_logging
test_logging_OBJECTS = \
"CMakeFiles/test_logging.dir/test/test_logging.cpp.o"

# External object files for target test_logging
test_logging_EXTERNAL_OBJECTS =

bin/test_logging: CMakeFiles/test_logging.dir/test/test_logging.cpp.o
bin/test_logging: CMakeFiles/test_logging.dir/build.make
bin/test_logging: lib/libeva02.so
bin/test_logging: CMakeFiles/test_logging.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/alfmunny/Projects/EVA02/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable bin/test_logging"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test_logging.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/test_logging.dir/build: bin/test_logging

.PHONY : CMakeFiles/test_logging.dir/build

CMakeFiles/test_logging.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/test_logging.dir/cmake_clean.cmake
.PHONY : CMakeFiles/test_logging.dir/clean

CMakeFiles/test_logging.dir/depend:
	cd /home/alfmunny/Projects/EVA02 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/alfmunny/Projects/EVA02 /home/alfmunny/Projects/EVA02 /home/alfmunny/Projects/EVA02 /home/alfmunny/Projects/EVA02 /home/alfmunny/Projects/EVA02/CMakeFiles/test_logging.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/test_logging.dir/depend

