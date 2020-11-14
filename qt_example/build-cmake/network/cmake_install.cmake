# Install script for directory: /home/jhon/Sublime_tests/qt_example/network

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "0")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/usr/bin/objdump")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/home/jhon/Sublime_tests/qt_example/build-cmake/network/multicastsender/cmake_install.cmake")
  include("/home/jhon/Sublime_tests/qt_example/build-cmake/network/multicastreceiver/cmake_install.cmake")
  include("/home/jhon/Sublime_tests/qt_example/build-cmake/network/bearermonitor/cmake_install.cmake")
  include("/home/jhon/Sublime_tests/qt_example/build-cmake/network/blockingfortuneclient/cmake_install.cmake")
  include("/home/jhon/Sublime_tests/qt_example/build-cmake/network/broadcastreceiver/cmake_install.cmake")
  include("/home/jhon/Sublime_tests/qt_example/build-cmake/network/broadcastsender/cmake_install.cmake")
  include("/home/jhon/Sublime_tests/qt_example/build-cmake/network/dnslookup/cmake_install.cmake")
  include("/home/jhon/Sublime_tests/qt_example/build-cmake/network/download/cmake_install.cmake")
  include("/home/jhon/Sublime_tests/qt_example/build-cmake/network/downloadmanager/cmake_install.cmake")
  include("/home/jhon/Sublime_tests/qt_example/build-cmake/network/fortuneclient/cmake_install.cmake")
  include("/home/jhon/Sublime_tests/qt_example/build-cmake/network/fortuneserver/cmake_install.cmake")
  include("/home/jhon/Sublime_tests/qt_example/build-cmake/network/googlesuggest/cmake_install.cmake")
  include("/home/jhon/Sublime_tests/qt_example/build-cmake/network/http/cmake_install.cmake")
  include("/home/jhon/Sublime_tests/qt_example/build-cmake/network/loopback/cmake_install.cmake")
  include("/home/jhon/Sublime_tests/qt_example/build-cmake/network/multistreamclient/cmake_install.cmake")
  include("/home/jhon/Sublime_tests/qt_example/build-cmake/network/multistreamserver/cmake_install.cmake")
  include("/home/jhon/Sublime_tests/qt_example/build-cmake/network/network-chat/cmake_install.cmake")
  include("/home/jhon/Sublime_tests/qt_example/build-cmake/network/threadedfortuneserver/cmake_install.cmake")
  include("/home/jhon/Sublime_tests/qt_example/build-cmake/network/torrent/cmake_install.cmake")
  include("/home/jhon/Sublime_tests/qt_example/build-cmake/network/secureudpclient/cmake_install.cmake")
  include("/home/jhon/Sublime_tests/qt_example/build-cmake/network/secureudpserver/cmake_install.cmake")

endif()

