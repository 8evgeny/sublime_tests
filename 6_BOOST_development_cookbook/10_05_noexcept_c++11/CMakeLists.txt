set(CMAKE_CXX_STANDARD 17)
   

ADD_EXECUTABLE(10_05_noexcept_c++11 main.cpp  )

 target_link_libraries(10_05_noexcept_c++11
    PUBLIC libpqxx
    PUBLIC boost_thread
    PUBLIC boost_system
    Qt5::Core
    Qt5::Widgets
        # CONFIG
        )



