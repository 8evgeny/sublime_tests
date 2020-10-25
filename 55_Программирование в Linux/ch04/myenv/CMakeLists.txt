set(CMAKE_CXX_STANDARD 17)

PROJECT (55_ch4_myenv)

# include_directories(printup   )
# FILE(GLOB SRC_FILES printup/*  )
FILE(GLOB SRC_FILES  *  )
add_executable(${PROJECT_NAME}  ${SRC_FILES})
# find_package(Qt5Core REQUIRED)
# find_package(Qt5Widgets REQUIRED)
# find_package(Qt5Sql REQUIRED)
target_link_libraries(${PROJECT_NAME}
  PUBLIC
#   ${Qt5Widgets_LIBRARIES}
#   ${Qt5Network_LIBRARIES}
#  Qt5::Core
#  Qt5::Widgets
)





                           


