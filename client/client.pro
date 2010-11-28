QT       += core dbus network
QT       -= gui

TARGET = mssf-client
CONFIG   += console
CONFIG   -= app_bundle
TEMPLATE = app

INCLUDEPATH += /usr/include/mssf/

SOURCES += main.cpp \
    mssfdbusif.cpp \
    serverdbus.cpp \
    client.cpp

HEADERS += mssfdbusif.h \
    serverdbus.h \
    client.h


OTHER_FILES +=


target.path = $$(DESTDIR)/usr/bin

INSTALLS += target
