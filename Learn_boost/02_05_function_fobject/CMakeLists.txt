set(CMAKE_CXX_STANDARD 17)
   

ADD_EXECUTABLE(02_05_function_fobject main.cpp  )

 target_link_libraries(02_05_function_fobject
    PUBLIC libpqxx
    PUBLIC boost_thread
    PUBLIC boost_system
    Qt5::Core
    Qt5::Widgets
        # CONFIG
        )



