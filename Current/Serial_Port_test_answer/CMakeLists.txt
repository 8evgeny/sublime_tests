set(CMAKE_CXX_STANDARD 17)

project (as_gyroplatphorm_RS485)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

include_directories(headers  sources xserial/src)
FILE(GLOB SRC_FILES sources/* headers/* )

add_executable(${PROJECT_NAME}
    ${SRC_FILES}
    )

target_link_libraries(${PROJECT_NAME}
  PUBLIC
  serial
)



                           


