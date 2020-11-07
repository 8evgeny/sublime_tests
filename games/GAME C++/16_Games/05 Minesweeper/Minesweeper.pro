TEMPLATE	= app
SOURCES		= main.cpp

LIBS += -L/usr/local/SFML/lib/ -lsfml-window
LIBS += -L/usr/local/SFML/lib/ -lsfml-graphics
LIBS += -L/usr/local/SFML/lib/ -lsfml-system
LIBS += -L/usr/local/SFML/lib/ -lsfml-network
LIBS += -L/usr/local/SFML/lib/ -lsfml-audio

INCLUDEPATH += /usr/local/SFML/include
DEPENDPATH +=  /usr/local/SFML/include

