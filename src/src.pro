QT       += dbus
QT       -= gui

TARGET = creds2-qt
TEMPLATE = lib

DEFINES += LIBCREDS2QT_LIBRARY

LIBS += -lcreds

SOURCES += \
    dbuscontextaccessmanager.cpp \
    credentialsmanager.cpp

HEADERS +=\
    dbuscontextaccessmanager.h \
    credentialsmanager.h \
    libcreds2-qt_global.h \
    DBusContextAccessManager \
    CredentialsManager

target.path = /usr/lib

headerfiles.files = $$HEADERS
headerfiles.path = /usr/include/libcreds2-qt

INSTALLS += target headerfiles
