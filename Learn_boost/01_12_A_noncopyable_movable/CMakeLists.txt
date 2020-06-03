set(CMAKE_CXX_STANDARD 17)
   

ADD_EXECUTABLE(01_12_A_noncopyable_movable main.cpp  )

 target_link_libraries(01_12_A_noncopyable_movable
    PUBLIC libpqxx
    PUBLIC boost_program_options
    Qt5::Core
    Qt5::Widgets
        # CONFIG
        )



