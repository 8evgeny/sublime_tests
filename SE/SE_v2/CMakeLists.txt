cmake_minimum_required(VERSION 3.5)

project(SE_v2 LANGUAGES CXX)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB
    src
    src_cpp/*
    include/*
    source/*
    forms/*
    )
find_package (Qt5Core)
find_package (Qt5Widgets)
find_package (Boost REQUIRED COMPONENTS
    system
    filesystem
    program_options
    )

SET(MYCOMPILE_FLAGS "-g -Wall -fPIC")
set(CMAKE_C_FLAGS ${MYCOMPILE_FLAGS})

add_executable(${PROJECT_NAME} ${src}
    main.cpp
    nativ.cpp
    functions.cpp
    muhurta.cpp
    panchang.cpp
    time.cpp
    findstartend.cpp
    qtPanchang.cpp
    scanHairCut.cpp
    )

target_include_directories(${PROJECT_NAME} PUBLIC include source forms)

target_link_libraries(${PROJECT_NAME}
-lm
-ldl
${Boost_LIBRARIES}
Qt5::Core
Qt5::Widgets
pthread
  )

set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(${PROJECT_NAME} PROPERTIES
            CXX_STANDARD 14
            CXX_EXTENSIONS ON
            )
set (CMAKE_LINKER_FLAGS "-leph -lm -ldl" )









