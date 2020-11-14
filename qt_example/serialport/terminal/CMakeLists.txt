set(CMAKE_CXX_STANDARD 17)

PROJECT (qt_example_serialport_terminal)

include_directories(headers sources resources)
FILE(GLOB SRC_FILES sources/* headers/* resources/* terminal.qrc )

find_package(Qt5 CONFIG REQUIRED Core Sql Widgets Gui PrintSupport SerialPort)

add_executable(${PROJECT_NAME}  ${SRC_FILES} terminal.qrc)


qt5_add_resources(terminal.qrc)

target_link_libraries(${PROJECT_NAME}
  PUBLIC
  ${Qt5Widgets_LIBRARIES}
  ${Qt5SQL_LIBRARIES}
  ${Qt5SerialPort_LIBRARIES}
  Qt5::Core
  Qt5::Widgets
  Qt5::Sql
  Qt5::SerialPort
  Qt5::Gui
  Qt5::PrintSupport
  )

#  CONFIG






                           


