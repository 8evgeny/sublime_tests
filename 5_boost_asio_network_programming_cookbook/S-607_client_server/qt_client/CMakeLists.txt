set(CMAKE_CXX_STANDARD 17)

PROJECT (qt_client)

include_directories(headers sources)
FILE(GLOB SRC_FILES sources/* headers/* )

find_package(Qt5 CONFIG REQUIRED Core Sql Widgets Gui Network)

add_executable(${PROJECT_NAME}  ${SRC_FILES})

target_link_libraries(${PROJECT_NAME}
  ${Qt5Widgets_LIBRARIES}
  ${Qt5Network_LIBRARIES}
  ${Qt5Core_LIBRARIES}
  ${Qt5Gui_LIBRARIES}
  pthread
  )

#target_include_directories(${PROJECT_NAME} ${SRC_FILES})

configure_file(config/config.ini ${CMAKE_CURRENT_BINARY_DIR}/config_qt_client.ini COPYONLY)


