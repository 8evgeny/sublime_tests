set(CMAKE_CXX_STANDARD 17)
   

ADD_EXECUTABLE(12_07_gil main.cpp)

 target_link_libraries(12_07_gil
    PUBLIC libpqxx
    PUBLIC boost_thread
    PUBLIC boost_system
    Qt5::Core
    Qt5::Widgets
        # CONFIG
        )



