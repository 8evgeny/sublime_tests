set(CMAKE_CXX_STANDARD 17)
   

ADD_EXECUTABLE(02_06_function_fpointer main.cpp  )

 target_link_libraries(02_06_function_fpointer
    PUBLIC libpqxx
    PUBLIC boost_thread
    PUBLIC boost_system
    Qt5::Core
    Qt5::Widgets
        # CONFIG
        )



