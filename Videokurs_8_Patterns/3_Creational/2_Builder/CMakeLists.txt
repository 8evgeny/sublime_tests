cmake_minimum_required(VERSION 3.5)

project(Creational_Builder)

add_executable(${PROJECT_NAME}_Builder  Builder.cpp)
add_executable(${PROJECT_NAME}_Facets
    Facets.cpp
    Person.cpp
    PersonBuilder.cpp
    )
add_executable(${PROJECT_NAME}_GroovyStyle  GroovyStyle.cpp)
add_executable(${PROJECT_NAME}_InnerFactory  InnerFactory.cpp)


set_target_properties(${PROJECT_NAME}_Builder  PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
        COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
        )
set_target_properties(${PROJECT_NAME}_Facets  PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
        COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
        )
set_target_properties(${PROJECT_NAME}_GroovyStyle  PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
        COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
        )
set_target_properties(${PROJECT_NAME}_InnerFactory  PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
        COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
        )
