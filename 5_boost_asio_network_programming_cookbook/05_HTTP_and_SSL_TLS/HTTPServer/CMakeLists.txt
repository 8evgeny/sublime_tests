set(CMAKE_CXX_STANDARD 17)

project(HTTP_and_SSL_TLS_HTTPServer)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(src HTTPServer.cpp)

ADD_EXECUTABLE(${PROJECT_NAME} ${src})

target_link_libraries(${PROJECT_NAME}
    /home/jhon/boost/boost_1_75_0/stage/lib/libboost_unit_test_framework.so
    /home/jhon/boost/boost_1_75_0/stage/lib/libboost_context.so
    /home/jhon/boost/boost_1_75_0/stage/lib/libboost_stacktrace_noop.so
    /home/jhon/boost/boost_1_75_0/stage/lib/libboost_regex.so
    /home/jhon/boost/boost_1_75_0/stage/lib/libboost_stacktrace_basic.so
    /home/jhon/boost/boost_1_75_0/stage/lib/libboost_wserialization.so
    /home/jhon/boost/boost_1_75_0/stage/lib/libboost_coroutine.so
    /home/jhon/boost/boost_1_75_0/stage/lib/libboost_graph.so
#    /home/jhon/boost/boost_1_75_0/stage/lib/libboost_python38.so
    /home/jhon/boost/boost_1_75_0/stage/lib/libboost_atomic.so
    /home/jhon/boost/boost_1_75_0/stage/lib/libboost_iostreams.so
    /home/jhon/boost/boost_1_75_0/stage/lib/libboost_locale.so
    /home/jhon/boost/boost_1_75_0/stage/lib/libboost_program_options.so
    /home/jhon/boost/boost_1_75_0/stage/lib/libboost_json.so
    /home/jhon/boost/boost_1_75_0/stage/lib/libboost_thread.so
    /home/jhon/boost/boost_1_75_0/stage/lib/libboost_math_tr1.so
    /home/jhon/boost/boost_1_75_0/stage/lib/libboost_system.so
    /home/jhon/boost/boost_1_75_0/stage/lib/libboost_stacktrace_addr2line.so
    /home/jhon/boost/boost_1_75_0/stage/lib/libboost_math_c99f.so
    /home/jhon/boost/boost_1_75_0/stage/lib/libboost_prg_exec_monitor.so
    /home/jhon/boost/boost_1_75_0/stage/lib/libboost_math_tr1f.so
    /home/jhon/boost/boost_1_75_0/stage/lib/libboost_chrono.so
    /home/jhon/boost/boost_1_75_0/stage/lib/libboost_math_c99l.so
    /home/jhon/boost/boost_1_75_0/stage/lib/libboost_type_erasure.so
    /home/jhon/boost/boost_1_75_0/stage/lib/libboost_filesystem.so
    /home/jhon/boost/boost_1_75_0/stage/lib/libboost_wave.so
    /home/jhon/boost/boost_1_75_0/stage/lib/libboost_math_tr1l.so
    /home/jhon/boost/boost_1_75_0/stage/lib/libboost_contract.so
    /home/jhon/boost/boost_1_75_0/stage/lib/libboost_container.so
    /home/jhon/boost/boost_1_75_0/stage/lib/libboost_random.so
    /home/jhon/boost/boost_1_75_0/stage/lib/libboost_log.so
    /home/jhon/boost/boost_1_75_0/stage/lib/libboost_nowide.so
    /home/jhon/boost/boost_1_75_0/stage/lib/libboost_timer.so
    /home/jhon/boost/boost_1_75_0/stage/lib/libboost_math_c99.so
    /home/jhon/boost/boost_1_75_0/stage/lib/libboost_date_time.so
    /home/jhon/boost/boost_1_75_0/stage/lib/libboost_fiber.so
    /home/jhon/boost/boost_1_75_0/stage/lib/libboost_serialization.so
    /home/jhon/boost/boost_1_75_0/stage/lib/libboost_log_setup.so







/usr/lib/libgnutls-openssl.so
/usr/lib/libpthread.so
    )
   





