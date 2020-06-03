set(CMAKE_CXX_STANDARD 17)
   

ADD_EXECUTABLE(06_01_tasks_processor_base main.cpp  tasks_processor_base.hpp)

 target_link_libraries(06_01_tasks_processor_base
    PUBLIC libpqxx
    PUBLIC boost_thread
    PUBLIC boost_system
    Qt5::Core
    Qt5::Widgets
        # CONFIG
        )



