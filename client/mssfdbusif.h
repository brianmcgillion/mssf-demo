/*
 * This file was generated by qdbusxml2cpp version 0.7
 * Command line was: qdbusxml2cpp -v -c MssfDbusIf -p mssfdbusif.h:mssfdbusif.cpp ./daemon/com.meego.mssf.xml
 *
 * qdbusxml2cpp is Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
 *
 * This is an auto-generated file.
 * Do not edit! All changes made to it will be lost.
 */

#ifndef MSSFDBUSIF_H_1289131697
#define MSSFDBUSIF_H_1289131697

#include <QtCore/QObject>
#include <QtCore/QByteArray>
#include <QtCore/QList>
#include <QtCore/QMap>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QVariant>
#include <QtDBus/QtDBus>

/*
 * Proxy class for interface com.meego.mssf
 */
class MssfDbusIf: public QDBusAbstractInterface
{
    Q_OBJECT
public:
    static inline const char *staticInterfaceName()
    { return "com.meego.mssf"; }

public:
    MssfDbusIf(const QString &service, const QString &path, const QDBusConnection &connection, QObject *parent = 0);

    ~MssfDbusIf();

public Q_SLOTS: // METHODS
    inline QDBusPendingReply<bool> setState(int state)
    {
        QList<QVariant> argumentList;
        argumentList << qVariantFromValue(state);
        return asyncCallWithArgumentList(QLatin1String("setState"), argumentList);
    }

Q_SIGNALS: // SIGNALS
};

namespace com {
  namespace meego {
    typedef ::MssfDbusIf mssf;
  }
}
#endif
