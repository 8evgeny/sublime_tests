set(CMAKE_CXX_STANDARD 17)
   

ADD_EXECUTABLE(10_07_my_library  my_library.cpp   my_library.hpp )

 target_link_libraries(10_07_my_library
    PUBLIC libpqxx
    PUBLIC boost_thread
    PUBLIC boost_system
    Qt5::Core
    Qt5::Widgets
        # CONFIG
        )



