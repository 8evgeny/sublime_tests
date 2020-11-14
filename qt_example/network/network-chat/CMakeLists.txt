set(CMAKE_CXX_STANDARD 17)

PROJECT (qt_example_network_network-chat)

include_directories(headers  sources )
FILE(GLOB SRC_FILES sources/* headers/* includes/*)
add_executable(${PROJECT_NAME}  ${SRC_FILES})
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Sql REQUIRED)
target_link_libraries(${PROJECT_NAME}
  PUBLIC
  ${Qt5Widgets_LIBRARIES}
  ${Qt5Network_LIBRARIES}
  Qt5::Core
  Qt5::Widgets
)





                           


