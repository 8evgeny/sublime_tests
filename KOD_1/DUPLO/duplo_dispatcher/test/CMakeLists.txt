

add_executable(duplo_dispatcher_test duplo_dispatcher_test.cpp)

target_link_libraries(duplo_dispatcher_test
  PUBLIC
  GTest::gtest
  GTest::gmock
  duplo_dispatcher_library
  )


add_test(NAME duplo_dispatcher_test COMMAND duplo_dispatcher_test)
