QT       += core dbus network
QT       -= gui

TARGET = mssfd
CONFIG   += console link_pkgconfig
CONFIG   -= app_bundle
PKGCONFIG += aegis-crypto
TEMPLATE = app

SOURCES += main.cpp \
    dbusserviceifadaptor.cpp \
    configuration.cpp \
    dbusservice.cpp \
    engine.cpp \
    configwriter.cpp \
    aegisstorage.cpp

HEADERS += \
    dbusserviceifadaptor.h \
    configuration.h \
    configuration_p.h \
    dbusservice.h \
    engine.h \
    engineconfigs.h \
    mssf-common.h \
    configwriter.h \
    aegisstorage.h

OTHER_FILES += \
    com.meego.mssf.xml \
    com.meego.mssf.service \
    com.meego.mssf.conf

target.path = $$(DESTDIR)/usr/bin

service.path = $$(DESTDIR)/usr/share/dbus-1/system-services
service.files = com.meego.mssf.service

configuration.path = $$(DESTDIR)/etc/dbus-1/system.d
configuration.files = com.meego.mssf.conf

dbusInterface.path = $$(DESTDIR)/usr/share/dbus-1/interfaces
dbusInterface.files = com.meego.mssf.xml

sharedHeader.path = $$(DESTDIR)/usr/include/mssf
sharedHeader.file = mssf-common.h

INSTALLS += target service configuration dbusInterface sharedHeader
