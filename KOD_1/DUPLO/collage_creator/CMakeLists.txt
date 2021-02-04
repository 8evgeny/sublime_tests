
cmake_minimum_required(VERSION 3.2)

set(srcs src/collage_creator.cpp)

add_library(collage_creator SHARED ${srcs})
add_library(sadko::collage_creator ALIAS collage_creator)

target_include_directories(collage_creator
  PUBLIC
    include
)

target_link_libraries(collage_creator
  PRIVATE
    sadko::imageutils
    sadko::domain
)
