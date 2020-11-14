# Install script for directory: /home/jhon/Sublime_tests/6_BOOST_development_cookbook

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
  include("/home/jhon/Sublime_tests/6_BOOST_development_cookbook/build-cmake/01_02_any/cmake_install.cmake")
  include("/home/jhon/Sublime_tests/6_BOOST_development_cookbook/build-cmake/01_03_variant/cmake_install.cmake")
  include("/home/jhon/Sublime_tests/6_BOOST_development_cookbook/build-cmake/01_04_A_any_db_example/cmake_install.cmake")
  include("/home/jhon/Sublime_tests/6_BOOST_development_cookbook/build-cmake/01_04_B_variant_db_example/cmake_install.cmake")
  include("/home/jhon/Sublime_tests/6_BOOST_development_cookbook/build-cmake/01_05_optional/cmake_install.cmake")
  include("/home/jhon/Sublime_tests/6_BOOST_development_cookbook/build-cmake/01_06_array/cmake_install.cmake")
  include("/home/jhon/Sublime_tests/6_BOOST_development_cookbook/build-cmake/01_07_A_tuple/cmake_install.cmake")
  include("/home/jhon/Sublime_tests/6_BOOST_development_cookbook/build-cmake/01_07_B_tuple_construction_order/cmake_install.cmake")
  include("/home/jhon/Sublime_tests/6_BOOST_development_cookbook/build-cmake/01_08_bind/cmake_install.cmake")
  include("/home/jhon/Sublime_tests/6_BOOST_development_cookbook/build-cmake/01_09_type_index/cmake_install.cmake")
  include("/home/jhon/Sublime_tests/6_BOOST_development_cookbook/build-cmake/01_10_A_move/cmake_install.cmake")
  include("/home/jhon/Sublime_tests/6_BOOST_development_cookbook/build-cmake/01_11_noncopyable/cmake_install.cmake")
  include("/home/jhon/Sublime_tests/6_BOOST_development_cookbook/build-cmake/01_12_A_noncopyable_movable/cmake_install.cmake")
  include("/home/jhon/Sublime_tests/6_BOOST_development_cookbook/build-cmake/01_13_algorithm/cmake_install.cmake")
  include("/home/jhon/Sublime_tests/6_BOOST_development_cookbook/build-cmake/02_01_scoped_ptr/cmake_install.cmake")
  include("/home/jhon/Sublime_tests/6_BOOST_development_cookbook/build-cmake/02_03_scoped_array/cmake_install.cmake")
  include("/home/jhon/Sublime_tests/6_BOOST_development_cookbook/build-cmake/02_05_function_fobject/cmake_install.cmake")
  include("/home/jhon/Sublime_tests/6_BOOST_development_cookbook/build-cmake/02_06_function_fpointer/cmake_install.cmake")
  include("/home/jhon/Sublime_tests/6_BOOST_development_cookbook/build-cmake/02_07_function_lambda_c++11/cmake_install.cmake")
  include("/home/jhon/Sublime_tests/6_BOOST_development_cookbook/build-cmake/02_08_ptr_container_c++11/cmake_install.cmake")
  include("/home/jhon/Sublime_tests/6_BOOST_development_cookbook/build-cmake/02_09_scope_exit/cmake_install.cmake")
  include("/home/jhon/Sublime_tests/6_BOOST_development_cookbook/build-cmake/02_10_base_from_member/cmake_install.cmake")
  include("/home/jhon/Sublime_tests/6_BOOST_development_cookbook/build-cmake/03_01_lexical_to_number/cmake_install.cmake")
  include("/home/jhon/Sublime_tests/6_BOOST_development_cookbook/build-cmake/03_02_lexical_to_string/cmake_install.cmake")
  include("/home/jhon/Sublime_tests/6_BOOST_development_cookbook/build-cmake/03_03_numeric_cast/cmake_install.cmake")
  include("/home/jhon/Sublime_tests/6_BOOST_development_cookbook/build-cmake/03_04_lexical_user_defined/cmake_install.cmake")
  include("/home/jhon/Sublime_tests/6_BOOST_development_cookbook/build-cmake/03_05_polymorphic_cast/cmake_install.cmake")
  include("/home/jhon/Sublime_tests/6_BOOST_development_cookbook/build-cmake/03_06_spirit/cmake_install.cmake")
  include("/home/jhon/Sublime_tests/6_BOOST_development_cookbook/build-cmake/03_07_spirit_rules/cmake_install.cmake")
  include("/home/jhon/Sublime_tests/6_BOOST_development_cookbook/build-cmake/04_01_conditional/cmake_install.cmake")
  include("/home/jhon/Sublime_tests/6_BOOST_development_cookbook/build-cmake/04_02_disable_if_c/cmake_install.cmake")
  include("/home/jhon/Sublime_tests/6_BOOST_development_cookbook/build-cmake/04_03_enable_if_c/cmake_install.cmake")
  include("/home/jhon/Sublime_tests/6_BOOST_development_cookbook/build-cmake/04_04_is_stdvector/cmake_install.cmake")
  include("/home/jhon/Sublime_tests/6_BOOST_development_cookbook/build-cmake/04_05_mpl_int_/cmake_install.cmake")
  include("/home/jhon/Sublime_tests/6_BOOST_development_cookbook/build-cmake/04_06_static_assert/cmake_install.cmake")
  include("/home/jhon/Sublime_tests/6_BOOST_development_cookbook/build-cmake/04_07_typeof/cmake_install.cmake")
  include("/home/jhon/Sublime_tests/6_BOOST_development_cookbook/build-cmake/06_01_tasks_processor_base/cmake_install.cmake")

endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/home/jhon/Sublime_tests/6_BOOST_development_cookbook/build-cmake/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
