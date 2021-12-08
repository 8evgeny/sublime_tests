set(CMAKE_CXX_STANDARD 17)

PROJECT (network_1_http)

include_directories(headers  sources )
FILE(GLOB SRC_FILES sources/* headers/* )

find_package(Qt5Widgets REQUIRED)
find_package(Qt5Network REQUIRED)

qt5_wrap_ui(SRC_FILES authenticationdialog.ui)

add_executable(${PROJECT_NAME}
    ${SRC_FILES}
    )

target_link_libraries(${PROJECT_NAME}
  PUBLIC
  ${Qt5Widgets_LIBRARIES}
  ${Qt5Network_LIBRARIES}
  Qt5::Core
  Qt5::Widgets
)





                           


