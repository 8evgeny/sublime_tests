add_subdirectory(widgets)

set(EXECUTABLE_PROPERTY )

if (WIN32)
    set(EXECUTABLE_PROPERTY WIN32)
endif (WIN32)

add_executable(duplo_sender ${EXECUTABLE_PROPERTY} "main.cpp")
target_link_libraries(duplo_sender 
    PUBLIC
       duplo_sender_widgets
)
