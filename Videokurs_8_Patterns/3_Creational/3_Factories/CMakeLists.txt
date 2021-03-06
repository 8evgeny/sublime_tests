cmake_minimum_required(VERSION 3.5)

project(Creational_Factories)

add_executable(${PROJECT_NAME}_AbstractFactory  AbstractFactory.cpp)
add_executable(${PROJECT_NAME}_FactoryMethod  FactoryMethod.cpp)
add_executable(${PROJECT_NAME}_InnerFactory  InnerFactory.cpp)



set_target_properties(${PROJECT_NAME}_AbstractFactory  PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
        COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
        )
set_target_properties(${PROJECT_NAME}_FactoryMethod  PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
        COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
        )
set_target_properties(${PROJECT_NAME}_InnerFactory  PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
        COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
        )
