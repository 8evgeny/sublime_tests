set(CMAKE_CXX_STANDARD 17)
   

ADD_EXECUTABLE(09_04_multiindex main.cpp  )

 target_link_libraries(09_04_multiindex
    PUBLIC libpqxx
    PUBLIC boost_thread
    PUBLIC boost_system
    Qt5::Core
    Qt5::Widgets
        # CONFIG
        )



