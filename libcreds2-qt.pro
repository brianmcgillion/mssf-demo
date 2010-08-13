TEMPLATE = subdirs
SUBDIRS  = src

PKGCONFIGFILES.files = libcreds2-qt.pc
PKGCONFIGFILES.path = /usr/lib/pkgconfig

QTCONFIGFILES.files = libcreds2-qt.prf
QTCONFIGFILES.path = /usr/share/qt4/mkspecs/features

INSTALLS += PKGCONFIGFILES QTCONFIGFILES
