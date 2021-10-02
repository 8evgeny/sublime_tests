project(${base_name} LANGUAGES CXX)
set(exe_name 8_Shared_pointers)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file (GLOB src *)

find_package(Qt5Core)
add_executable(${PROJECT_NAME}_${exe_name}
    ${src})

set_target_properties(${PROJECT_NAME}_${exe_name}  PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
    )
target_link_libraries(${PROJECT_NAME}_${exe_name}
    Qt5::Core)



