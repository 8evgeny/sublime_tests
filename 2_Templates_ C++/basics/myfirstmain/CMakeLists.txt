set(CMAKE_CXX_STANDARD 17)

project(basics_myfirstmain)


ADD_EXECUTABLE(${PROJECT_NAME} myfirstmain.cpp  myfirst.hpp ../myfirst/myfirst.cpp  ../myfirst/myfirst.hpp)
#target_link_libraries(${PROJECT_NAME}
#    basics_myfirst
#    )



