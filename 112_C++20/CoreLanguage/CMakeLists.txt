set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -pthread -fcoroutines -fmodules-ts")

add_executable(core_1  abbreviatedFunctionTemplates.cpp)
add_executable(core_2  aggregateInitialization.cpp)
add_executable(core_3  allAnyNone.cpp)
add_executable(core_4  bitField.cpp)
add_executable(core_5  char8Str.cpp)
#add_executable(core_6  client.cpp) #Требуется сперва собрать модуль math
#...Еще много файлов
