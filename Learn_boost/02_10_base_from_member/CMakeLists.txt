set(CMAKE_CXX_STANDARD 17)
   

ADD_EXECUTABLE(02_10_base_from_member main.cpp  )

 target_link_libraries(02_10_base_from_member
    PUBLIC libpqxx
    PUBLIC boost_thread
    PUBLIC boost_system
    Qt5::Core
    Qt5::Widgets
        # CONFIG
        )



