TEMPLATE = lib
CONFIG += plugin qmltypes
QT += qml quick

QML_IMPORT_NAME = Charts
QML_IMPORT_MAJOR_VERSION = 1

TARGET = $$qtLibraryTarget(chartsplugin)

HEADERS += piechart.h \
           pieslice.h \
           chartsplugin.h

SOURCES += piechart.cpp \
           pieslice.cpp

DESTPATH=$$[QT_INSTALL_EXAMPLES]/qml/tutorials/extending-qml/chapter6-plugins/$$QML_IMPORT_NAME

target.path=$$DESTPATH
qmldir.files=$$PWD/qmldir
qmldir.path=$$DESTPATH
INSTALLS += target qmldir

CONFIG += install_ok  # Do not cargo-cult this!

OTHER_FILES += qmldir

# Copy the qmldir file to the same folder as the plugin binary
cpqmldir.files = qmldir
cpqmldir.path = .
COPIES += cpqmldir
