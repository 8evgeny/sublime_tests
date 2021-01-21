set(CMAKE_CXX_STANDARD 17)
project(test2)
set(src
test2.cpp
test2.h
)
find_package (Qt5Core)
find_package (Qt5Widgets)

add_executable(${PROJECT_NAME} ${src} )

 target_link_libraries(
     ${PROJECT_NAME}
     Qt5::Core
     Qt5::Widgets
     )
