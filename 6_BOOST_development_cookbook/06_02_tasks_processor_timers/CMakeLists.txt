set(CMAKE_CXX_STANDARD 17)

project(06_02_tasks_processor_timers)

file(GLOB src *
    ../06_01_tasks_processor_base/tasks_processor_base.hpp
    )

#ADD_EXECUTABLE(${PROJECT_NAME} main.cpp tasks_processor_timers.hpp)
ADD_EXECUTABLE(${PROJECT_NAME} ${src})
set (Boost_NO_SYSTEM_PATHS ON)
set (Boost_USE_MULTITHREADED ON)
set (Boost_USE_STATIC_LIBS ON)
set (Boost_USE_STATIC_RUNTIME OFF)
set (BOOST_ALL_DYN_LINK OFF)


find_package (Boost REQUIRED COMPONENTS  chrono timer context thread system filesystem)

if (Boost_FOUND)
    message(${Boost_INCLUDE_DIR})
    include_directories (SYSTEM ${Boost_INCLUDE_DIR})
endif ()

target_link_libraries(
    ${PROJECT_NAME}
    ${Boost_LIBRARIES}
    )



