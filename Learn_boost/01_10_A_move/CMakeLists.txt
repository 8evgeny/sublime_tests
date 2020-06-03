set(CMAKE_CXX_STANDARD 17)
   

ADD_EXECUTABLE(01_10_A_move main.cpp  )

 target_link_libraries(01_10_A_move
    PUBLIC libpqxx
    PUBLIC boost_program_options
    Qt5::Core
    Qt5::Widgets
        # CONFIG
        )



