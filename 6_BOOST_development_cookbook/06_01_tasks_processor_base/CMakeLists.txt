#set(CMAKE_CXX_STANDARD 17)
#project(06_01_tasks_processor_base)
#ADD_EXECUTABLE(${PROJECT_NAME} main.cpp tasks_processor_base.hpp )
#set (Boost_NO_SYSTEM_PATHS ON)
#set (Boost_USE_MULTITHREADED ON)
#set (Boost_USE_STATIC_LIBS ON)
#set (Boost_USE_STATIC_RUNTIME OFF)
#set (BOOST_ALL_DYN_LINK OFF)
#find_package (Boost REQUIRED )#COMPONENTS  thread system filesystem)
#if (Boost_FOUND)
#    message("cmake message-" ${PROJECT_NAME} " boost include DIR: " ${Boost_INCLUDE_DIR})
#    include_directories (SYSTEM ${Boost_INCLUDE_DIR})
#endif ()
#target_link_libraries(
#    ${PROJECT_NAME}
#    ${Boost_LIBRARIES}
#    )


project(06_01_tasks_processor_base)

include(${CMAKE_SOURCE_DIR}/${PROJECT_NAME}/conanbuildinfo.cmake)
conan_basic_setup()

add_executable(${PROJECT_NAME} main.cpp tasks_processor_base.hpp)

set_target_properties(
    ${PROJECT_NAME}
    PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
    COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
    )
target_link_libraries(${PROJECT_NAME}
    ${CONAN_LIBS}
    )
