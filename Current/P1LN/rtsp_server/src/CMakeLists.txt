#add_executable(rtsp_server gst-rtsp-launch.cpp)
add_executable(rtsp_server p1LN.cpp)

target_link_libraries(rtsp_server PUBLIC GST_RTSP_SERVER)

install(TARGETS rtsp_server
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib/static
)
