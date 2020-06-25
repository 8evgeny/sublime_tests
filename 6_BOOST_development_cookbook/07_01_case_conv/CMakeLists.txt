set(CMAKE_CXX_STANDARD 17)
   

ADD_EXECUTABLE(07_01_case_conv main.cpp  )

 target_link_libraries(07_01_case_conv
    PUBLIC libpqxx
    PUBLIC boost_thread
    PUBLIC boost_system
    Qt5::Core
    Qt5::Widgets
        # CONFIG
        )



