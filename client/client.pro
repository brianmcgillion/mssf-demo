QT       += core dbus network
QT       -= gui

TARGET = mssf-client
CONFIG   += console link_pkgconfig
CONFIG   -= app_bundle
PKGCONFIG += aegis-crypto mssf-shared-lib
TEMPLATE = app

INCLUDEPATH += /usr/include/mssf/

SOURCES += main.cpp \
    mssfdbusif.cpp \
    serverdbus.cpp \
    client.cpp \
    ../daemon/aegiscrypto.cpp

HEADERS += mssfdbusif.h \
    serverdbus.h \
    client.h \
    ../daemon/aegiscrypto.h

target.path = $$(DESTDIR)/usr/bin

INSTALLS += target

OTHER_FILES += \
    client.aegis.xml
