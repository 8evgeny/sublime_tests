set(CMAKE_CXX_STANDARD 17)
   

ADD_EXECUTABLE(04_05_mpl_int_ main.cpp  )

 target_link_libraries(04_05_mpl_int_
    PUBLIC libpqxx
    PUBLIC boost_thread
    PUBLIC boost_system
    Qt5::Core
    Qt5::Widgets
        # CONFIG
        )



