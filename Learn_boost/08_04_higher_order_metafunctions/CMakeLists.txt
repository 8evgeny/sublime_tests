set(CMAKE_CXX_STANDARD 17)
   

ADD_EXECUTABLE(08_04_higher_order_metafunctions main.cpp  )

 target_link_libraries(08_04_higher_order_metafunctions
    PUBLIC libpqxx
    PUBLIC boost_thread
    PUBLIC boost_system
    Qt5::Core
    Qt5::Widgets
        # CONFIG
        )



