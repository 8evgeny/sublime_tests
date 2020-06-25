set(CMAKE_CXX_STANDARD 17)
   

ADD_EXECUTABLE(03_02_lexical_to_string main.cpp  )

 target_link_libraries(03_02_lexical_to_string
    PUBLIC libpqxx
    PUBLIC boost_thread
    PUBLIC boost_system
    Qt5::Core
    Qt5::Widgets
        # CONFIG
        )



