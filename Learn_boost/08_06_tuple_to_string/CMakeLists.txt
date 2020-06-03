set(CMAKE_CXX_STANDARD 17)
   

ADD_EXECUTABLE(08_06_tuple_to_string main.cpp  )

 target_link_libraries(08_06_tuple_to_string
    PUBLIC libpqxx
    PUBLIC boost_thread
    PUBLIC boost_system
    Qt5::Core
    Qt5::Widgets
        # CONFIG
        )



