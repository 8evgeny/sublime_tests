set(CMAKE_CXX_STANDARD 17)

project (range_temp_position_sensor)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/run )
include_directories(headers  sources )
FILE(GLOB SRC_FILES sources/* headers/* )

find_package(Qt5Widgets REQUIRED)
find_package(Qt5Network REQUIRED)

add_executable(${PROJECT_NAME}
    ${SRC_FILES}
    )

qt5_use_modules(${PROJECT_NAME} Core SerialPort)

target_link_libraries(${PROJECT_NAME}
  PUBLIC
  ${Qt5Widgets_LIBRARIES}
  ${Qt5Network_LIBRARIES}
  Qt5::Core
  Qt5::Widgets
  -lrt -lpthread
)



                           


