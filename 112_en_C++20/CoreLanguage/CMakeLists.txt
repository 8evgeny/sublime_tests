set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -pthread -fcoroutines -fmodules-ts")

add_executable(CoreLanguage_abbreviatedFunctionTemplates  abbreviatedFunctionTemplates.cpp)
add_executable(CoreLanguage_aggregateInitialization  aggregateInitialization.cpp)
add_executable(CoreLanguage_allAnyNone  allAnyNone.cpp)
add_executable(CoreLanguage_bitField  bitField.cpp)
add_executable(CoreLanguage_char8Str  char8Str.cpp)
#add_executable(core_6  client.cpp) #Требуется сперва собрать модуль math
#...Еще много файлов
