set(CMAKE_CXX_STANDARD 17)
cmake_minimum_required(VERSION 3.5)
project(simpleDB)
set(src
src/simpleDB.cpp
src/simpleDB.h
)

find_package (Qt5Core)
find_package (Qt5Widgets)

add_executable(${PROJECT_NAME} ${src} )
target_link_libraries(
  ${PROJECT_NAME}
  Qt5::Core
  Qt5::Widgets
  )
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/config/configDB.ini
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
