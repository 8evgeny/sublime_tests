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
CMAKE_SOURCE_DIR = /home/jhon/Sublime_tests/6_BOOST_development_cookbook

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/jhon/Sublime_tests/6_BOOST_development_cookbook/build-cmake

# Include any dependencies generated for this target.
include 04_04_is_stdvector/CMakeFiles/04_04_is_stdvector.dir/depend.make

# Include the progress variables for this target.
include 04_04_is_stdvector/CMakeFiles/04_04_is_stdvector.dir/progress.make

# Include the compile flags for this target's objects.
include 04_04_is_stdvector/CMakeFiles/04_04_is_stdvector.dir/flags.make

04_04_is_stdvector/CMakeFiles/04_04_is_stdvector.dir/main.o: 04_04_is_stdvector/CMakeFiles/04_04_is_stdvector.dir/flags.make
04_04_is_stdvector/CMakeFiles/04_04_is_stdvector.dir/main.o: ../04_04_is_stdvector/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jhon/Sublime_tests/6_BOOST_development_cookbook/build-cmake/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object 04_04_is_stdvector/CMakeFiles/04_04_is_stdvector.dir/main.o"
	cd /home/jhon/Sublime_tests/6_BOOST_development_cookbook/build-cmake/04_04_is_stdvector && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/04_04_is_stdvector.dir/main.o -c /home/jhon/Sublime_tests/6_BOOST_development_cookbook/04_04_is_stdvector/main.cpp

04_04_is_stdvector/CMakeFiles/04_04_is_stdvector.dir/main.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/04_04_is_stdvector.dir/main.i"
	cd /home/jhon/Sublime_tests/6_BOOST_development_cookbook/build-cmake/04_04_is_stdvector && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jhon/Sublime_tests/6_BOOST_development_cookbook/04_04_is_stdvector/main.cpp > CMakeFiles/04_04_is_stdvector.dir/main.i

04_04_is_stdvector/CMakeFiles/04_04_is_stdvector.dir/main.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/04_04_is_stdvector.dir/main.s"
	cd /home/jhon/Sublime_tests/6_BOOST_development_cookbook/build-cmake/04_04_is_stdvector && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jhon/Sublime_tests/6_BOOST_development_cookbook/04_04_is_stdvector/main.cpp -o CMakeFiles/04_04_is_stdvector.dir/main.s

# Object files for target 04_04_is_stdvector
04_04_is_stdvector_OBJECTS = \
"CMakeFiles/04_04_is_stdvector.dir/main.o"

# External object files for target 04_04_is_stdvector
04_04_is_stdvector_EXTERNAL_OBJECTS =

04_04_is_stdvector/04_04_is_stdvector: 04_04_is_stdvector/CMakeFiles/04_04_is_stdvector.dir/main.o
04_04_is_stdvector/04_04_is_stdvector: 04_04_is_stdvector/CMakeFiles/04_04_is_stdvector.dir/build.make
04_04_is_stdvector/04_04_is_stdvector: 04_04_is_stdvector/CMakeFiles/04_04_is_stdvector.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/jhon/Sublime_tests/6_BOOST_development_cookbook/build-cmake/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable 04_04_is_stdvector"
	cd /home/jhon/Sublime_tests/6_BOOST_development_cookbook/build-cmake/04_04_is_stdvector && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/04_04_is_stdvector.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
04_04_is_stdvector/CMakeFiles/04_04_is_stdvector.dir/build: 04_04_is_stdvector/04_04_is_stdvector

.PHONY : 04_04_is_stdvector/CMakeFiles/04_04_is_stdvector.dir/build

04_04_is_stdvector/CMakeFiles/04_04_is_stdvector.dir/clean:
	cd /home/jhon/Sublime_tests/6_BOOST_development_cookbook/build-cmake/04_04_is_stdvector && $(CMAKE_COMMAND) -P CMakeFiles/04_04_is_stdvector.dir/cmake_clean.cmake
.PHONY : 04_04_is_stdvector/CMakeFiles/04_04_is_stdvector.dir/clean

04_04_is_stdvector/CMakeFiles/04_04_is_stdvector.dir/depend:
	cd /home/jhon/Sublime_tests/6_BOOST_development_cookbook/build-cmake && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jhon/Sublime_tests/6_BOOST_development_cookbook /home/jhon/Sublime_tests/6_BOOST_development_cookbook/04_04_is_stdvector /home/jhon/Sublime_tests/6_BOOST_development_cookbook/build-cmake /home/jhon/Sublime_tests/6_BOOST_development_cookbook/build-cmake/04_04_is_stdvector /home/jhon/Sublime_tests/6_BOOST_development_cookbook/build-cmake/04_04_is_stdvector/CMakeFiles/04_04_is_stdvector.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : 04_04_is_stdvector/CMakeFiles/04_04_is_stdvector.dir/depend
