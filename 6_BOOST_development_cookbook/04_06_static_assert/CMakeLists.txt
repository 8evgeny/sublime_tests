set(CMAKE_CXX_STANDARD 17)
   

ADD_EXECUTABLE(04_06_static_assert main.cpp  )

 target_link_libraries(04_06_static_assert
    PUBLIC libpqxx
    PUBLIC boost_thread
    PUBLIC boost_system
    Qt5::Core
    Qt5::Widgets
        # CONFIG
        )



