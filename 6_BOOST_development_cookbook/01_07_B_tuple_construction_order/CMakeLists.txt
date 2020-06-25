set(CMAKE_CXX_STANDARD 17)
   

ADD_EXECUTABLE(01_07_B_tuple_construction_order main.cpp  )

target_link_libraries(01_07_B_tuple_construction_order
    PUBLIC libpqxx
    PUBLIC boost_program_options
    Qt5::Core
    Qt5::Widgets
        # CONFIG
        )



