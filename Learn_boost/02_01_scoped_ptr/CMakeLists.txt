set(CMAKE_CXX_STANDARD 17)
   

ADD_EXECUTABLE(02_01_scoped_ptr main.cpp  )

 target_link_libraries(02_01_scoped_ptr
    PUBLIC libpqxx
    PUBLIC boost_program_options
    Qt5::Core
    Qt5::Widgets
        # CONFIG
        )



