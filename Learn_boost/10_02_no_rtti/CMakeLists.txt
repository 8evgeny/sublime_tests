set(CMAKE_CXX_STANDARD 17)
   

ADD_EXECUTABLE(10_02_no_rtti main.cpp  )

 target_link_libraries(10_02_no_rtti
    PUBLIC libpqxx
    PUBLIC boost_thread
    PUBLIC boost_system
    Qt5::Core
    Qt5::Widgets
        # CONFIG
        )



