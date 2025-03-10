QT += waylandclient gui-private
CONFIG += wayland-scanner

WAYLANDCLIENTSOURCES += ../protocol/custom.xml

SOURCES += main.cpp \
    ../client-common/customextension.cpp

HEADERS += \
    ../client-common/customextension.h

TARGET = custom-extension-cpp-client

target.path = $$[QT_INSTALL_EXAMPLES]/wayland/custom-extension/cpp-client
INSTALLS += target
