project(12_07_gil)

include(${CMAKE_SOURCE_DIR}/${PROJECT_NAME}/conanbuildinfo.cmake)
conan_basic_setup()

#Пример
#conan_cmake_configure(REQUIRES
#                      boost/1.69.0
#                      GENERATORS cmake_find_package)

#conan_cmake_autodetect(settings)

#conan_cmake_install(PATH_OR_REFERENCE .
#                    BUILD missing
#                    REMOTE conancenter
#                    SETTINGS ${settings})


find_package (Boost REQUIRED COMPONENTS  ALL)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    link_directories(${Boost_LIBRARY_DIRS})
    add_definitions(${Boost_DEFINITIONS})
endif()
add_executable(${PROJECT_NAME} main.cpp)

set_target_properties(
    ${PROJECT_NAME}
    PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
    COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
    )
target_link_libraries(${PROJECT_NAME}
    ${CONAN_LIBS}
    -lpng
    ${Boost_LIBRARIES}
    Boost::gil
    )
