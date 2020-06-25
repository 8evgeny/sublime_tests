set(CMAKE_CXX_STANDARD 17)
   

ADD_EXECUTABLE(10_03_extern_template main.cpp    source.cpp   header.hpp)

 target_link_libraries(10_03_extern_template
    PUBLIC libpqxx
    PUBLIC boost_thread
    PUBLIC boost_system
    Qt5::Core
    Qt5::Widgets
        # CONFIG
        )



