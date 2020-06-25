set(CMAKE_CXX_STANDARD 17)
   

ADD_EXECUTABLE(04_07_typeof main.cpp  )

 target_link_libraries(04_07_typeof
    PUBLIC libpqxx
    PUBLIC boost_thread
    PUBLIC boost_system
    Qt5::Core
    Qt5::Widgets
        # CONFIG
        )



