project(handle_message)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} \
    -std=c++20 \
    -pthread \
    -fcoroutines \
    -fmodules-ts" )

#find_package(Qt5Widgets REQUIRED)
#find_package(Qt5Network REQUIRED)

file(GLOB src *.cpp)
add_executable(${PROJECT_NAME}  ${src})

#target_link_libraries(${PROJECT_NAME}
#  PUBLIC
#  ${Qt5Widgets_LIBRARIES}
#  ${Qt5Network_LIBRARIES}
#  Qt5::Core
#  Qt5::Widgets
#)
