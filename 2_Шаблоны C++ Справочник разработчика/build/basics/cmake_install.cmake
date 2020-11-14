# Install script for directory: /home/jhon/Sublime_tests/2_Шаблоны C++ Справочник разработчика/basics

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
  include("/home/jhon/Sublime_tests/2_Шаблоны C++ Справочник разработчика/build/basics/arrays/cmake_install.cmake")
  include("/home/jhon/Sublime_tests/2_Шаблоны C++ Справочник разработчика/build/basics/foreach/cmake_install.cmake")
  include("/home/jhon/Sublime_tests/2_Шаблоны C++ Справочник разработчика/build/basics/foreachinvoke/cmake_install.cmake")
  include("/home/jhon/Sublime_tests/2_Шаблоны C++ Справочник разработчика/build/basics/max1/cmake_install.cmake")
  include("/home/jhon/Sublime_tests/2_Шаблоны C++ Справочник разработчика/build/basics/max2/cmake_install.cmake")
  include("/home/jhon/Sublime_tests/2_Шаблоны C++ Справочник разработчика/build/basics/max3ref/cmake_install.cmake")
  include("/home/jhon/Sublime_tests/2_Шаблоны C++ Справочник разработчика/build/basics/max3val/cmake_install.cmake")
  include("/home/jhon/Sublime_tests/2_Шаблоны C++ Справочник разработчика/build/basics/max4/cmake_install.cmake")
  include("/home/jhon/Sublime_tests/2_Шаблоны C++ Справочник разработчика/build/basics/cref/cmake_install.cmake")
  include("/home/jhon/Sublime_tests/2_Шаблоны C++ Справочник разработчика/build/basics/stack1/cmake_install.cmake")
  include("/home/jhon/Sublime_tests/2_Шаблоны C++ Справочник разработчика/build/basics/stack3/cmake_install.cmake")
  include("/home/jhon/Sublime_tests/2_Шаблоны C++ Справочник разработчика/build/basics/stack9/cmake_install.cmake")
  include("/home/jhon/Sublime_tests/2_Шаблоны C++ Справочник разработчика/build/basics/stacknontype/cmake_install.cmake")
  include("/home/jhon/Sublime_tests/2_Шаблоны C++ Справочник разработчика/build/basics/stackauto/cmake_install.cmake")
  include("/home/jhon/Sublime_tests/2_Шаблоны C++ Справочник разработчика/build/basics/tmplparamref/cmake_install.cmake")
  include("/home/jhon/Sublime_tests/2_Шаблоны C++ Справочник разработчика/build/basics/message/cmake_install.cmake")
  include("/home/jhon/Sublime_tests/2_Шаблоны C++ Справочник разработчика/build/basics/move1/cmake_install.cmake")
  include("/home/jhon/Sublime_tests/2_Шаблоны C++ Справочник разработчика/build/basics/move2/cmake_install.cmake")
  include("/home/jhon/Sublime_tests/2_Шаблоны C++ Справочник разработчика/build/basics/varusing/cmake_install.cmake")
  include("/home/jhon/Sublime_tests/2_Шаблоны C++ Справочник разработчика/build/basics/specialmemtmpl1/cmake_install.cmake")
  include("/home/jhon/Sublime_tests/2_Шаблоны C++ Справочник разработчика/build/basics/specialmemtmpl3/cmake_install.cmake")
  include("/home/jhon/Sublime_tests/2_Шаблоны C++ Справочник разработчика/build/basics/foldtraverse/cmake_install.cmake")

endif()

