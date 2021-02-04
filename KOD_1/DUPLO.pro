TEMPLATE	= app
#QMAKE_CXXFLAGS += "-Wno-old-style-cast"
SOURCES		=  \
    duplo_dispatcher.cpp \
    duplo_dispatcher_exception.cpp \
    duplo_main_window.cpp \
    images_model.cpp \
    images_table.cpp \
    main.cpp \
    violation_order.cpp \
    violation_order_widget.cpp
QT             += widgets


HEADERS += \
    MessengerServiceSoapBinding.nsmap \
    duplo_dispatcher.h \
    duplo_dispatcher_exception.h \
    duplo_main_window.h \
    images_model.h \
    images_table.h \
    soapMessengerServiceSoapBindingProxy.h \
    violation_order.h \
    violation_order_widget.h




