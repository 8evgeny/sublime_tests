set(CMAKE_CXX_STANDARD 17)

project(11_06_reading_files)
ADD_EXECUTABLE(${PROJECT_NAME} main.cpp )

set (Boost_NO_SYSTEM_PATHS ON)
set (Boost_USE_MULTITHREADED ON)
set (Boost_USE_STATIC_LIBS ON)
set (Boost_USE_STATIC_RUNTIME OFF)
set (BOOST_ALL_DYN_LINK OFF)

find_package (Boost REQUIRED COMPONENTS
    regex
    filesystem
    chrono
    system
    thread
    timer
    context
    date_time
    math_c99f
    type_erasure
    stacktrace_basic
    log_setup
    contract
    stacktrace_noop
    locale
    math_tr1
    math_c99
    math_c99l
    random
    prg_exec_monitor
    numpy39
    fiber
    wave
    nowide
    program_options
    graph_parallel
    mpi
    mpi_python39
    coroutine
    graph
    container
    stacktrace_addr2line
    log
    unit_test_framework
    iostreams
    serialization
    atomic
    math_tr1l
    python39
    math_tr1f
    wserialization

       )

if (Boost_FOUND)
    message("cmake message-" ${PROJECT_NAME} " boost include DIR: " ${Boost_INCLUDE_DIR})
    include_directories (SYSTEM ${Boost_INCLUDE_DIR})
endif ()

target_link_libraries(
    ${PROJECT_NAME}
    ${Boost_LIBRARIES}
#    my_library
    )



