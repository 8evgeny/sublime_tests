set(CMAKE_CXX_STANDARD 17)
   

ADD_EXECUTABLE(08_02_manipulating_vector_of_types main.cpp  )

 target_link_libraries(08_02_manipulating_vector_of_types
    PUBLIC libpqxx
    PUBLIC boost_thread
    PUBLIC boost_system
    Qt5::Core
    Qt5::Widgets
        # CONFIG
        )



