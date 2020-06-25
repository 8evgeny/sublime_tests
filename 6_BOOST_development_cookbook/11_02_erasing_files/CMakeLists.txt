set(CMAKE_CXX_STANDARD 17)
   

ADD_EXECUTABLE(11_02_erasing_files main.cpp)

 target_link_libraries(11_02_erasing_files
    PUBLIC libpqxx
    PUBLIC boost_thread
    PUBLIC boost_system
    Qt5::Core
    Qt5::Widgets
        # CONFIG
        )



