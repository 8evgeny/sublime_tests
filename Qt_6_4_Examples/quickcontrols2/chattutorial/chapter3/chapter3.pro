TEMPLATE = app

QT += qml quick
CONFIG += c++11

SOURCES += main.cpp

RESOURCES += \
    ContactPage.qml \
    ConversationPage.qml \
    images/Albert_Einstein.png \
    images/Albert_Einstein@2x.png \
    images/Albert_Einstein@3x.png \
    images/Albert_Einstein@4x.png \
    images/Ernest_Hemingway.png \
    images/Ernest_Hemingway@2x.png \
    images/Ernest_Hemingway@3x.png \
    images/Ernest_Hemingway@4x.png \
    images/Hans_Gude.png \
    images/Hans_Gude@2x.png \
    images/Hans_Gude@3x.png \
    images/Hans_Gude@4x.png \
    main.qml \
    qtquickcontrols2.conf

target.path = $$[QT_INSTALL_EXAMPLES]/quickcontrols2/chattutorial/chapter3
INSTALLS += target
