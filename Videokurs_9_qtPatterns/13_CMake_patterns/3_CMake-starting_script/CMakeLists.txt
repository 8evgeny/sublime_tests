project(${base_name} LANGUAGES CXX)
set(exe_name 3_CMake-starting_script)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file (GLOB src *)

find_package(Qt5 COMPONENTS Core REQUIRED)
add_executable(${PROJECT_NAME}_${exe_name}
    ${src})

set_target_properties(${PROJECT_NAME}_${exe_name}  PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
    )
target_link_libraries(${PROJECT_NAME}_${exe_name}
    PRIVATE
    Qt5::Core)

#PRE_BUILD - run before all other dependencies
#PRE_LINK - run after other dependencies
#POST_BUILD - run after the target has been built

#Нужно делать rebuild - смотреть сообщения компилятора
add_custom_command(
    TARGET ${PROJECT_NAME}_${exe_name} PRE_BUILD
    COMMAND python3 ${CMAKE_CURRENT_SOURCE_DIR}/test.py prebuild
)

add_custom_command(
    TARGET ${PROJECT_NAME}_${exe_name} PRE_LINK
    COMMAND python3 ${CMAKE_CURRENT_SOURCE_DIR}/test.py prelink
)

add_custom_command(
    TARGET ${PROJECT_NAME}_${exe_name} POST_BUILD
    COMMAND python3 ${CMAKE_CURRENT_SOURCE_DIR}/test.py postbuild
)

