set(LIB_NAME duplo_dispatcher_library)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")

   message(STATUS "Duplo_dispatcher_flags: ${COMPILE_FLAGS}")

   set_source_files_properties(
         ../duplo_generated/stdsoap2.cpp
         ../duplo_generated/soapMessengerServiceSoapBindingProxy.cpp
         ../duplo_generated/soapC.cpp
      PROPERTIES COMPILE_FLAGS
          "-w"
   )

endif()

add_library(${LIB_NAME} SHARED
        src/duplo_dispatcher.cpp
        src/duplo_dispatcher_exception.cpp
        ../duplo_generated/stdsoap2.cpp
        ../duplo_generated/soapMessengerServiceSoapBindingProxy.cpp
        ../duplo_generated/soapC.cpp
        )



target_include_directories(${LIB_NAME}
   PUBLIC
      include
      ../duplo_generated
)

target_link_libraries(${LIB_NAME}
   PUBLIC
      violation_order_library
)

add_subdirectory(test)
