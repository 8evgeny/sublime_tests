set(TSAN_UNIT_TEST_SOURCES
  tsan_clock_test.cpp
  tsan_dense_alloc_test.cpp
  tsan_flags_test.cpp
  tsan_ilist_test.cpp
  tsan_mman_test.cpp
  tsan_shadow_test.cpp
  tsan_stack_test.cpp
  tsan_sync_test.cpp
  tsan_unit_test_main.cpp
  )

add_tsan_unittest(TsanUnitTest
  SOURCES ${TSAN_UNIT_TEST_SOURCES})
