set(CMAKE_CXX_STANDARD 17)
   

ADD_EXECUTABLE(10_08_version main.cpp  )

 target_link_libraries(10_08_version
    PUBLIC libpqxx
    PUBLIC boost_thread
    PUBLIC boost_system
    Qt5::Core
    Qt5::Widgets
        # CONFIG
        )



