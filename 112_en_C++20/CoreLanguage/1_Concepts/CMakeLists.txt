set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  \
    -pthread \
    -fcoroutines \
    -fmodules-ts")
project(1_Concepts)
add_executable(CoreLanguage_${PROJECT_NAME}_1_tooSpecific  1_tooSpecific.cpp)
add_executable(CoreLanguage_${PROJECT_NAME}_2_tooGeneric  2_tooGeneric.cpp)
add_executable(CoreLanguage_${PROJECT_NAME}_3_IntegralVariations  3_conceptsIntegralVariations.cpp)
#add_executable(CoreLanguage_${PROJECT_NAME}_4_IntegralVariations  3_conceptsIntegralVariations.cpp)
