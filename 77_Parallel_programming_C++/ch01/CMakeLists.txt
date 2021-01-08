FIND_PACKAGE( TBB REQUIRED COMPONENTS tbb tbbmalloc tbbmalloc_proxy
    tbb_preview
)
include_directories(${TBB_DIR})
SET(GXX_TBB_FLAGS    "-ltbb")
set (CMAKE_CXX_FLAGS ${GXX_TBB_FLAGS})
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS}
    -ltbb
    -lpthread
    -ldl
    -lm")
add_executable (1_fig_1_04  ch01.h fig_1_07.cpp)

target_link_libraries(1_fig_1_04
    ${TBB_LIBS}
    tbb
tbbmalloc
tbbmalloc_proxy
    )
