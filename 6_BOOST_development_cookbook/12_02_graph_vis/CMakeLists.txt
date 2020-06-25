set(CMAKE_CXX_STANDARD 17)
   

ADD_EXECUTABLE(12_02_graph_vis main.cpp)

 target_link_libraries(12_02_graph_vis
    PUBLIC libpqxx
    PUBLIC boost_thread
    PUBLIC boost_system
    Qt5::Core
    Qt5::Widgets
        # CONFIG
        )



