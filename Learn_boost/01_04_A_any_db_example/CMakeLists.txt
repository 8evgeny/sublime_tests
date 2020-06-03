set(CMAKE_CXX_STANDARD 17)
   

ADD_EXECUTABLE(01_04_A_any_db_example main.cpp  )

 target_link_libraries(01_04_A_any_db_example
    PUBLIC libpqxx
    PUBLIC boost_program_options
    Qt5::Core
    Qt5::Widgets
        # CONFIG
        )



