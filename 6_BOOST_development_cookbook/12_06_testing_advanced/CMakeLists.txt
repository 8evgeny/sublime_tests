set(CMAKE_CXX_STANDARD 17)
   

ADD_EXECUTABLE(12_06_testing_advanced main.cpp developer1.cpp developer2.cpp foo.cpp foo.hpp ) 

 target_link_libraries(12_06_testing_advanced
    PUBLIC libpqxx
    PUBLIC boost_thread
    PUBLIC boost_system
    Qt5::Core
    Qt5::Widgets
        # CONFIG
        )



