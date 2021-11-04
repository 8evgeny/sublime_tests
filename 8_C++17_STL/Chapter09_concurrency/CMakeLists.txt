set(CMAKE_CXX_STANDARD 17)

project(9_concurrency)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

#add_executable(${PROJECT_NAME}_async async.cpp)
add_executable(${PROJECT_NAME}_auto_parallel auto_parallel.cpp)
#add_executable(${PROJECT_NAME}_avoid_deadlock avoid_deadlock.cpp)

#target_link_libraries(${PROJECT_NAME}_async pthread)
target_link_libraries(${PROJECT_NAME}_auto_parallel pthread)
#target_link_libraries(${PROJECT_NAME}_avoid_deadlock pthread)
