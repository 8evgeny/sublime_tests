set(CMAKE_CXX_STANDARD 17)

PROJECT (boost_client)

include_directories(headers sources)
FILE(GLOB SRC_FILES sources/* headers/* )

find_package(Qt5 CONFIG REQUIRED Core Sql Widgets Gui)

add_executable(${PROJECT_NAME}  ${SRC_FILES})


target_link_libraries(${PROJECT_NAME}
  ${Qt5Widgets_LIBRARIES}
  pthread
  )

#target_include_directories(${PROJECT_NAME} ${SRC_FILES})

configure_file(config/config.ini ${CMAKE_CURRENT_BINARY_DIR}/config_boost_client.ini COPYONLY)

