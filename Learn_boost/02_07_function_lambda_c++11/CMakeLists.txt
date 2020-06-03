set(CMAKE_CXX_STANDARD 17)
   

ADD_EXECUTABLE(02_07_function_lambda_c++11 main.cpp  )

 target_link_libraries(02_07_function_lambda_c++11
    PUBLIC libpqxx
    PUBLIC boost_thread
    PUBLIC boost_system
    Qt5::Core
    Qt5::Widgets
        # CONFIG
        )



