project(${base_name} LANGUAGES CXX)
set(exe_name 7_Update_GUI_QML_from_thread)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file (GLOB src *)

include(${CMAKE_SOURCE_DIR}/06_Thread_patterns/7_Update_GUI_QML_from_thread/conanbuildinfo.cmake)
#conan_basic_setup()

set(RESOURCE_FILES
    qml.qrc
    )


find_package(Qt5 COMPONENTS Core Widgets Qml REQUIRED)
add_executable(${PROJECT_NAME}_${exe_name}
    ${src})

set_target_properties(${PROJECT_NAME}_${exe_name}  PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
    )

target_link_libraries(${PROJECT_NAME}_${exe_name}
    PRIVATE
#    ${CONAN_LIBS}
    Qt5::Widgets
    Qt5::Qml
    Qt5::Core
    )



