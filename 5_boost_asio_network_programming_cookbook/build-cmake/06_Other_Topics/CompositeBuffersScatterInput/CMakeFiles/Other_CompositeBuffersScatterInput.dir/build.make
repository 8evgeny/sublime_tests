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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/jhon/Sublime_tests/5_boost_asio_network_programming_cookbook

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/jhon/Sublime_tests/5_boost_asio_network_programming_cookbook/build-cmake

# Include any dependencies generated for this target.
include 06_Other_Topics/CompositeBuffersScatterInput/CMakeFiles/Other_CompositeBuffersScatterInput.dir/depend.make

# Include the progress variables for this target.
include 06_Other_Topics/CompositeBuffersScatterInput/CMakeFiles/Other_CompositeBuffersScatterInput.dir/progress.make

# Include the compile flags for this target's objects.
include 06_Other_Topics/CompositeBuffersScatterInput/CMakeFiles/Other_CompositeBuffersScatterInput.dir/flags.make

06_Other_Topics/CompositeBuffersScatterInput/CMakeFiles/Other_CompositeBuffersScatterInput.dir/CompositeBuffersScatterInput.cpp.o: 06_Other_Topics/CompositeBuffersScatterInput/CMakeFiles/Other_CompositeBuffersScatterInput.dir/flags.make
06_Other_Topics/CompositeBuffersScatterInput/CMakeFiles/Other_CompositeBuffersScatterInput.dir/CompositeBuffersScatterInput.cpp.o: ../06_Other_Topics/CompositeBuffersScatterInput/CompositeBuffersScatterInput.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jhon/Sublime_tests/5_boost_asio_network_programming_cookbook/build-cmake/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object 06_Other_Topics/CompositeBuffersScatterInput/CMakeFiles/Other_CompositeBuffersScatterInput.dir/CompositeBuffersScatterInput.cpp.o"
	cd /home/jhon/Sublime_tests/5_boost_asio_network_programming_cookbook/build-cmake/06_Other_Topics/CompositeBuffersScatterInput && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Other_CompositeBuffersScatterInput.dir/CompositeBuffersScatterInput.cpp.o -c /home/jhon/Sublime_tests/5_boost_asio_network_programming_cookbook/06_Other_Topics/CompositeBuffersScatterInput/CompositeBuffersScatterInput.cpp

06_Other_Topics/CompositeBuffersScatterInput/CMakeFiles/Other_CompositeBuffersScatterInput.dir/CompositeBuffersScatterInput.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Other_CompositeBuffersScatterInput.dir/CompositeBuffersScatterInput.cpp.i"
	cd /home/jhon/Sublime_tests/5_boost_asio_network_programming_cookbook/build-cmake/06_Other_Topics/CompositeBuffersScatterInput && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jhon/Sublime_tests/5_boost_asio_network_programming_cookbook/06_Other_Topics/CompositeBuffersScatterInput/CompositeBuffersScatterInput.cpp > CMakeFiles/Other_CompositeBuffersScatterInput.dir/CompositeBuffersScatterInput.cpp.i

06_Other_Topics/CompositeBuffersScatterInput/CMakeFiles/Other_CompositeBuffersScatterInput.dir/CompositeBuffersScatterInput.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Other_CompositeBuffersScatterInput.dir/CompositeBuffersScatterInput.cpp.s"
	cd /home/jhon/Sublime_tests/5_boost_asio_network_programming_cookbook/build-cmake/06_Other_Topics/CompositeBuffersScatterInput && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jhon/Sublime_tests/5_boost_asio_network_programming_cookbook/06_Other_Topics/CompositeBuffersScatterInput/CompositeBuffersScatterInput.cpp -o CMakeFiles/Other_CompositeBuffersScatterInput.dir/CompositeBuffersScatterInput.cpp.s

# Object files for target Other_CompositeBuffersScatterInput
Other_CompositeBuffersScatterInput_OBJECTS = \
"CMakeFiles/Other_CompositeBuffersScatterInput.dir/CompositeBuffersScatterInput.cpp.o"

# External object files for target Other_CompositeBuffersScatterInput
Other_CompositeBuffersScatterInput_EXTERNAL_OBJECTS =

06_Other_Topics/CompositeBuffersScatterInput/Other_CompositeBuffersScatterInput: 06_Other_Topics/CompositeBuffersScatterInput/CMakeFiles/Other_CompositeBuffersScatterInput.dir/CompositeBuffersScatterInput.cpp.o
06_Other_Topics/CompositeBuffersScatterInput/Other_CompositeBuffersScatterInput: 06_Other_Topics/CompositeBuffersScatterInput/CMakeFiles/Other_CompositeBuffersScatterInput.dir/build.make
06_Other_Topics/CompositeBuffersScatterInput/Other_CompositeBuffersScatterInput: /home/jhon/boost/boost_1_75_0/stage/lib/libboost_system.so
06_Other_Topics/CompositeBuffersScatterInput/Other_CompositeBuffersScatterInput: /home/jhon/boost/boost_1_75_0/stage/lib/libboost_thread.so
06_Other_Topics/CompositeBuffersScatterInput/Other_CompositeBuffersScatterInput: /usr/lib/libpthread.so
06_Other_Topics/CompositeBuffersScatterInput/Other_CompositeBuffersScatterInput: 06_Other_Topics/CompositeBuffersScatterInput/CMakeFiles/Other_CompositeBuffersScatterInput.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/jhon/Sublime_tests/5_boost_asio_network_programming_cookbook/build-cmake/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Other_CompositeBuffersScatterInput"
	cd /home/jhon/Sublime_tests/5_boost_asio_network_programming_cookbook/build-cmake/06_Other_Topics/CompositeBuffersScatterInput && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Other_CompositeBuffersScatterInput.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
06_Other_Topics/CompositeBuffersScatterInput/CMakeFiles/Other_CompositeBuffersScatterInput.dir/build: 06_Other_Topics/CompositeBuffersScatterInput/Other_CompositeBuffersScatterInput

.PHONY : 06_Other_Topics/CompositeBuffersScatterInput/CMakeFiles/Other_CompositeBuffersScatterInput.dir/build

06_Other_Topics/CompositeBuffersScatterInput/CMakeFiles/Other_CompositeBuffersScatterInput.dir/clean:
	cd /home/jhon/Sublime_tests/5_boost_asio_network_programming_cookbook/build-cmake/06_Other_Topics/CompositeBuffersScatterInput && $(CMAKE_COMMAND) -P CMakeFiles/Other_CompositeBuffersScatterInput.dir/cmake_clean.cmake
.PHONY : 06_Other_Topics/CompositeBuffersScatterInput/CMakeFiles/Other_CompositeBuffersScatterInput.dir/clean

06_Other_Topics/CompositeBuffersScatterInput/CMakeFiles/Other_CompositeBuffersScatterInput.dir/depend:
	cd /home/jhon/Sublime_tests/5_boost_asio_network_programming_cookbook/build-cmake && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jhon/Sublime_tests/5_boost_asio_network_programming_cookbook /home/jhon/Sublime_tests/5_boost_asio_network_programming_cookbook/06_Other_Topics/CompositeBuffersScatterInput /home/jhon/Sublime_tests/5_boost_asio_network_programming_cookbook/build-cmake /home/jhon/Sublime_tests/5_boost_asio_network_programming_cookbook/build-cmake/06_Other_Topics/CompositeBuffersScatterInput /home/jhon/Sublime_tests/5_boost_asio_network_programming_cookbook/build-cmake/06_Other_Topics/CompositeBuffersScatterInput/CMakeFiles/Other_CompositeBuffersScatterInput.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : 06_Other_Topics/CompositeBuffersScatterInput/CMakeFiles/Other_CompositeBuffersScatterInput.dir/depend
