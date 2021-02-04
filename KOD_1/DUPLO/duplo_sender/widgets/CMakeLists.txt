add_library(duplo_sender_widgets
    src/duplo_main_window.cpp

    # widgets
    src/violation_order_widget.h
    src/violation_order_widget.cpp

    src/images_model.h
    src/images_model.cpp
)

target_link_libraries(duplo_sender_widgets 
   PUBLIC 
      Qt5::Core Qt5::Widgets Qt5::Sql
      duplo_dispatcher_library
      easy_profiler
)

target_include_directories(duplo_sender_widgets
   PUBLIC 
      include 
      src
   )
