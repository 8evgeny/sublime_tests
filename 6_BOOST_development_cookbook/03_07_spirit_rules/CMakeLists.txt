set(CMAKE_CXX_STANDARD 17)
   

ADD_EXECUTABLE(03_07_spirit_rules main.cpp  )

 target_link_libraries(03_07_spirit_rules
    PUBLIC libpqxx
    PUBLIC boost_thread
    PUBLIC boost_system
    Qt5::Core
    Qt5::Widgets
        # CONFIG
        )



