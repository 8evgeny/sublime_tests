QT += core gui qml

QT += waylandcompositor

CONFIG += wayland-scanner
CONFIG += c++11
SOURCES += \
    main.cpp \
    customextension.cpp

OTHER_FILES = \
    qml/main.qml \
    qml/CompositorScreen.qml \
    images/background.jpg

WAYLANDSERVERSOURCES += \
            ../protocol/custom.xml

RESOURCES += compositor.qrc

TARGET = custom-extension-compositor

HEADERS += \
    customextension.h

target.path = $$[QT_INSTALL_EXAMPLES]/wayland/custom-extension/compositor
INSTALLS += target
