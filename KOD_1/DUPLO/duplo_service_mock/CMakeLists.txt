cmake_minimum_required(VERSION 3.2)

set (srcs src/duplo_service_mock.cpp
          ../gsoap_generated/soapC.cpp
          ../gsoap_generated/stdsoap2.cpp
          ../gsoap_generated/soapMessengerServiceSoapBindingService.cpp
    )

add_executable(duplo_mock ${srcs})


if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
   set_source_files_properties(
      ../gsoap_generated/soapC.cpp
      ../gsoap_generated/stdsoap2.cpp
      ../gsoap_generated/soapMessengerServiceSoapBindingService.cpp
      PROPERTIES COMPILE_FLAGS
          "-w"
   )
endif()


target_include_directories(duplo_mock
  PUBLIC
    include
    ${CMAKE_CURRENT_BINARY_DIR}
  PRIVATE
    src
    ../gsoap_generated
)

target_link_libraries(duplo_mock
PRIVATE
  Boost::boost
  Boost::program_options
 # base64
)
