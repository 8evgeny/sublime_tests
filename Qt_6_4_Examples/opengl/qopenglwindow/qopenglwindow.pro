TEMPLATE = app
TARGET = qopenglwindow
INCLUDEPATH += .
QT += opengl

RESOURCES += shaders.qrc

SOURCES += \
    main.cpp \
    background_renderer.cpp

HEADERS += \
    background_renderer.h

target.path = $$[QT_INSTALL_EXAMPLES]/opengl/qopenglwindow
INSTALLS += target
