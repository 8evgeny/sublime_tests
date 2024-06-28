project(arguscamerarenderer)

set(SOURCES
    Composer.cpp
    StreamConsumer.cpp
    )

include_directories(
    ${CMAKE_SOURCE_DIR}/apps/camera/common
    ${CMAKE_SOURCE_DIR}/apps/camera/modules
    ${CMAKE_SOURCE_DIR}/samples/utils
    ${ARGUS_INCLUDE_DIR}
    ${OPENGLES_INCLUDE_DIR}
    ${EGL_INCLUDE_DIR}
    )

add_library(${PROJECT_NAME} STATIC ${SOURCES})

target_link_libraries(${PROJECT_NAME}
    ${OPENGLES_LIBRARIES}
    ${EGL_LIBRARIES}
    arguscameracommon
    arguscameramodules
    argussampleutils
    )
