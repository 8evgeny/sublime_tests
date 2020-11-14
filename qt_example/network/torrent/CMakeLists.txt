set(CMAKE_CXX_STANDARD 17)

PROJECT (qt_example_network_torrent)

include_directories(headers  sources includes  sources/icons  sources/forms )
FILE(GLOB SRC_FILES sources/* headers/* includes/* forms/* icons/* icons)
add_executable(${PROJECT_NAME}  ${SRC_FILES}  sources/icons.qrc)
find_package(Qt5 CONFIG REQUIRED Core Network Sql Widgets Gui PrintSupport SerialPort)

set ( RESOURCES
 icons.qrc
 sources/*
)
QT5_ADD_RESOURCES(${RESOURCES})
qt5_add_resources( RES_SOURCES ${RESOURCES} )

target_link_libraries(${PROJECT_NAME}
  PUBLIC
  ${Qt5Widgets_LIBRARIES}
  ${Qt5SQL_LIBRARIES}
  ${Qt5SerialPort_LIBRARIES}
  Qt5::Core
  Qt5::Network
  Qt5::Widgets
  Qt5::Sql
  Qt5::SerialPort
  Qt5::Gui
  Qt5::PrintSupport
)





                           


