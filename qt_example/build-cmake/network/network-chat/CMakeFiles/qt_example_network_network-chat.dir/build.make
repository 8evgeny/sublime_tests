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
CMAKE_SOURCE_DIR = /home/jhon/Sublime_tests/qt_example

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/jhon/Sublime_tests/qt_example/build-cmake

# Include any dependencies generated for this target.
include network/network-chat/CMakeFiles/qt_example_network_network-chat.dir/depend.make

# Include the progress variables for this target.
include network/network-chat/CMakeFiles/qt_example_network_network-chat.dir/progress.make

# Include the compile flags for this target's objects.
include network/network-chat/CMakeFiles/qt_example_network_network-chat.dir/flags.make

network/network-chat/CMakeFiles/qt_example_network_network-chat.dir/sources/chatdialog.o: network/network-chat/CMakeFiles/qt_example_network_network-chat.dir/flags.make
network/network-chat/CMakeFiles/qt_example_network_network-chat.dir/sources/chatdialog.o: ../network/network-chat/sources/chatdialog.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jhon/Sublime_tests/qt_example/build-cmake/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object network/network-chat/CMakeFiles/qt_example_network_network-chat.dir/sources/chatdialog.o"
	cd /home/jhon/Sublime_tests/qt_example/build-cmake/network/network-chat && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/qt_example_network_network-chat.dir/sources/chatdialog.o -c /home/jhon/Sublime_tests/qt_example/network/network-chat/sources/chatdialog.cpp

network/network-chat/CMakeFiles/qt_example_network_network-chat.dir/sources/chatdialog.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/qt_example_network_network-chat.dir/sources/chatdialog.i"
	cd /home/jhon/Sublime_tests/qt_example/build-cmake/network/network-chat && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jhon/Sublime_tests/qt_example/network/network-chat/sources/chatdialog.cpp > CMakeFiles/qt_example_network_network-chat.dir/sources/chatdialog.i

network/network-chat/CMakeFiles/qt_example_network_network-chat.dir/sources/chatdialog.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/qt_example_network_network-chat.dir/sources/chatdialog.s"
	cd /home/jhon/Sublime_tests/qt_example/build-cmake/network/network-chat && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jhon/Sublime_tests/qt_example/network/network-chat/sources/chatdialog.cpp -o CMakeFiles/qt_example_network_network-chat.dir/sources/chatdialog.s

network/network-chat/CMakeFiles/qt_example_network_network-chat.dir/sources/client.o: network/network-chat/CMakeFiles/qt_example_network_network-chat.dir/flags.make
network/network-chat/CMakeFiles/qt_example_network_network-chat.dir/sources/client.o: ../network/network-chat/sources/client.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jhon/Sublime_tests/qt_example/build-cmake/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object network/network-chat/CMakeFiles/qt_example_network_network-chat.dir/sources/client.o"
	cd /home/jhon/Sublime_tests/qt_example/build-cmake/network/network-chat && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/qt_example_network_network-chat.dir/sources/client.o -c /home/jhon/Sublime_tests/qt_example/network/network-chat/sources/client.cpp

network/network-chat/CMakeFiles/qt_example_network_network-chat.dir/sources/client.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/qt_example_network_network-chat.dir/sources/client.i"
	cd /home/jhon/Sublime_tests/qt_example/build-cmake/network/network-chat && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jhon/Sublime_tests/qt_example/network/network-chat/sources/client.cpp > CMakeFiles/qt_example_network_network-chat.dir/sources/client.i

network/network-chat/CMakeFiles/qt_example_network_network-chat.dir/sources/client.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/qt_example_network_network-chat.dir/sources/client.s"
	cd /home/jhon/Sublime_tests/qt_example/build-cmake/network/network-chat && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jhon/Sublime_tests/qt_example/network/network-chat/sources/client.cpp -o CMakeFiles/qt_example_network_network-chat.dir/sources/client.s

network/network-chat/CMakeFiles/qt_example_network_network-chat.dir/sources/connection.o: network/network-chat/CMakeFiles/qt_example_network_network-chat.dir/flags.make
network/network-chat/CMakeFiles/qt_example_network_network-chat.dir/sources/connection.o: ../network/network-chat/sources/connection.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jhon/Sublime_tests/qt_example/build-cmake/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object network/network-chat/CMakeFiles/qt_example_network_network-chat.dir/sources/connection.o"
	cd /home/jhon/Sublime_tests/qt_example/build-cmake/network/network-chat && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/qt_example_network_network-chat.dir/sources/connection.o -c /home/jhon/Sublime_tests/qt_example/network/network-chat/sources/connection.cpp

network/network-chat/CMakeFiles/qt_example_network_network-chat.dir/sources/connection.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/qt_example_network_network-chat.dir/sources/connection.i"
	cd /home/jhon/Sublime_tests/qt_example/build-cmake/network/network-chat && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jhon/Sublime_tests/qt_example/network/network-chat/sources/connection.cpp > CMakeFiles/qt_example_network_network-chat.dir/sources/connection.i

network/network-chat/CMakeFiles/qt_example_network_network-chat.dir/sources/connection.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/qt_example_network_network-chat.dir/sources/connection.s"
	cd /home/jhon/Sublime_tests/qt_example/build-cmake/network/network-chat && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jhon/Sublime_tests/qt_example/network/network-chat/sources/connection.cpp -o CMakeFiles/qt_example_network_network-chat.dir/sources/connection.s

network/network-chat/CMakeFiles/qt_example_network_network-chat.dir/sources/main.o: network/network-chat/CMakeFiles/qt_example_network_network-chat.dir/flags.make
network/network-chat/CMakeFiles/qt_example_network_network-chat.dir/sources/main.o: ../network/network-chat/sources/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jhon/Sublime_tests/qt_example/build-cmake/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object network/network-chat/CMakeFiles/qt_example_network_network-chat.dir/sources/main.o"
	cd /home/jhon/Sublime_tests/qt_example/build-cmake/network/network-chat && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/qt_example_network_network-chat.dir/sources/main.o -c /home/jhon/Sublime_tests/qt_example/network/network-chat/sources/main.cpp

network/network-chat/CMakeFiles/qt_example_network_network-chat.dir/sources/main.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/qt_example_network_network-chat.dir/sources/main.i"
	cd /home/jhon/Sublime_tests/qt_example/build-cmake/network/network-chat && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jhon/Sublime_tests/qt_example/network/network-chat/sources/main.cpp > CMakeFiles/qt_example_network_network-chat.dir/sources/main.i

network/network-chat/CMakeFiles/qt_example_network_network-chat.dir/sources/main.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/qt_example_network_network-chat.dir/sources/main.s"
	cd /home/jhon/Sublime_tests/qt_example/build-cmake/network/network-chat && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jhon/Sublime_tests/qt_example/network/network-chat/sources/main.cpp -o CMakeFiles/qt_example_network_network-chat.dir/sources/main.s

network/network-chat/CMakeFiles/qt_example_network_network-chat.dir/sources/peermanager.o: network/network-chat/CMakeFiles/qt_example_network_network-chat.dir/flags.make
network/network-chat/CMakeFiles/qt_example_network_network-chat.dir/sources/peermanager.o: ../network/network-chat/sources/peermanager.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jhon/Sublime_tests/qt_example/build-cmake/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object network/network-chat/CMakeFiles/qt_example_network_network-chat.dir/sources/peermanager.o"
	cd /home/jhon/Sublime_tests/qt_example/build-cmake/network/network-chat && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/qt_example_network_network-chat.dir/sources/peermanager.o -c /home/jhon/Sublime_tests/qt_example/network/network-chat/sources/peermanager.cpp

network/network-chat/CMakeFiles/qt_example_network_network-chat.dir/sources/peermanager.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/qt_example_network_network-chat.dir/sources/peermanager.i"
	cd /home/jhon/Sublime_tests/qt_example/build-cmake/network/network-chat && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jhon/Sublime_tests/qt_example/network/network-chat/sources/peermanager.cpp > CMakeFiles/qt_example_network_network-chat.dir/sources/peermanager.i

network/network-chat/CMakeFiles/qt_example_network_network-chat.dir/sources/peermanager.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/qt_example_network_network-chat.dir/sources/peermanager.s"
	cd /home/jhon/Sublime_tests/qt_example/build-cmake/network/network-chat && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jhon/Sublime_tests/qt_example/network/network-chat/sources/peermanager.cpp -o CMakeFiles/qt_example_network_network-chat.dir/sources/peermanager.s

network/network-chat/CMakeFiles/qt_example_network_network-chat.dir/sources/server.o: network/network-chat/CMakeFiles/qt_example_network_network-chat.dir/flags.make
network/network-chat/CMakeFiles/qt_example_network_network-chat.dir/sources/server.o: ../network/network-chat/sources/server.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jhon/Sublime_tests/qt_example/build-cmake/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object network/network-chat/CMakeFiles/qt_example_network_network-chat.dir/sources/server.o"
	cd /home/jhon/Sublime_tests/qt_example/build-cmake/network/network-chat && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/qt_example_network_network-chat.dir/sources/server.o -c /home/jhon/Sublime_tests/qt_example/network/network-chat/sources/server.cpp

network/network-chat/CMakeFiles/qt_example_network_network-chat.dir/sources/server.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/qt_example_network_network-chat.dir/sources/server.i"
	cd /home/jhon/Sublime_tests/qt_example/build-cmake/network/network-chat && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jhon/Sublime_tests/qt_example/network/network-chat/sources/server.cpp > CMakeFiles/qt_example_network_network-chat.dir/sources/server.i

network/network-chat/CMakeFiles/qt_example_network_network-chat.dir/sources/server.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/qt_example_network_network-chat.dir/sources/server.s"
	cd /home/jhon/Sublime_tests/qt_example/build-cmake/network/network-chat && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jhon/Sublime_tests/qt_example/network/network-chat/sources/server.cpp -o CMakeFiles/qt_example_network_network-chat.dir/sources/server.s

# Object files for target qt_example_network_network-chat
qt_example_network_network__chat_OBJECTS = \
"CMakeFiles/qt_example_network_network-chat.dir/sources/chatdialog.o" \
"CMakeFiles/qt_example_network_network-chat.dir/sources/client.o" \
"CMakeFiles/qt_example_network_network-chat.dir/sources/connection.o" \
"CMakeFiles/qt_example_network_network-chat.dir/sources/main.o" \
"CMakeFiles/qt_example_network_network-chat.dir/sources/peermanager.o" \
"CMakeFiles/qt_example_network_network-chat.dir/sources/server.o"

# External object files for target qt_example_network_network-chat
qt_example_network_network__chat_EXTERNAL_OBJECTS =

network/network-chat/qt_example_network_network-chat: network/network-chat/CMakeFiles/qt_example_network_network-chat.dir/sources/chatdialog.o
network/network-chat/qt_example_network_network-chat: network/network-chat/CMakeFiles/qt_example_network_network-chat.dir/sources/client.o
network/network-chat/qt_example_network_network-chat: network/network-chat/CMakeFiles/qt_example_network_network-chat.dir/sources/connection.o
network/network-chat/qt_example_network_network-chat: network/network-chat/CMakeFiles/qt_example_network_network-chat.dir/sources/main.o
network/network-chat/qt_example_network_network-chat: network/network-chat/CMakeFiles/qt_example_network_network-chat.dir/sources/peermanager.o
network/network-chat/qt_example_network_network-chat: network/network-chat/CMakeFiles/qt_example_network_network-chat.dir/sources/server.o
network/network-chat/qt_example_network_network-chat: network/network-chat/CMakeFiles/qt_example_network_network-chat.dir/build.make
network/network-chat/qt_example_network_network-chat: /home/jhon/Qt/5.14.2/gcc_64/lib/libQt5Widgets.so.5.14.2
network/network-chat/qt_example_network_network-chat: /home/jhon/Qt/5.14.2/gcc_64/lib/libQt5Gui.so.5.14.2
network/network-chat/qt_example_network_network-chat: /home/jhon/Qt/5.14.2/gcc_64/lib/libQt5Core.so.5.14.2
network/network-chat/qt_example_network_network-chat: network/network-chat/CMakeFiles/qt_example_network_network-chat.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/jhon/Sublime_tests/qt_example/build-cmake/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Linking CXX executable qt_example_network_network-chat"
	cd /home/jhon/Sublime_tests/qt_example/build-cmake/network/network-chat && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/qt_example_network_network-chat.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
network/network-chat/CMakeFiles/qt_example_network_network-chat.dir/build: network/network-chat/qt_example_network_network-chat

.PHONY : network/network-chat/CMakeFiles/qt_example_network_network-chat.dir/build

network/network-chat/CMakeFiles/qt_example_network_network-chat.dir/clean:
	cd /home/jhon/Sublime_tests/qt_example/build-cmake/network/network-chat && $(CMAKE_COMMAND) -P CMakeFiles/qt_example_network_network-chat.dir/cmake_clean.cmake
.PHONY : network/network-chat/CMakeFiles/qt_example_network_network-chat.dir/clean

network/network-chat/CMakeFiles/qt_example_network_network-chat.dir/depend:
	cd /home/jhon/Sublime_tests/qt_example/build-cmake && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jhon/Sublime_tests/qt_example /home/jhon/Sublime_tests/qt_example/network/network-chat /home/jhon/Sublime_tests/qt_example/build-cmake /home/jhon/Sublime_tests/qt_example/build-cmake/network/network-chat /home/jhon/Sublime_tests/qt_example/build-cmake/network/network-chat/CMakeFiles/qt_example_network_network-chat.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : network/network-chat/CMakeFiles/qt_example_network_network-chat.dir/depend
