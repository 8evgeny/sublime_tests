set(CMAKE_CXX_STANDARD 17)
   

ADD_EXECUTABLE(08_03_result_of_c++11 main.cpp  )

 target_link_libraries(08_03_result_of_c++11
    PUBLIC libpqxx
    PUBLIC boost_thread
    PUBLIC boost_system
    Qt5::Core
    Qt5::Widgets
        # CONFIG
        )



