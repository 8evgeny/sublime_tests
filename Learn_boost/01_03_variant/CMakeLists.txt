set(CMAKE_CXX_STANDARD 17)
   

ADD_EXECUTABLE(01_01_03_variant main.cpp  )

 target_link_libraries(01_01_03_variant
    PUBLIC libpqxx
    PUBLIC boost_program_options
    Qt5::Core
    Qt5::Widgets
        # CONFIG
        )



