#include "smacklabelif.h"
#include <QList>
#include <QVariant>
#include <QLatin1String>

namespace Constants
{
    //! DBus service
    static const QLatin1String DBusService("org.freedesktop.DBus");
    //! DBus path
    static const QLatin1String DBusPath("/");
}

SmackLabelIf::SmackLabelIf(QObject *parent)
  : QDBusAbstractInterface(Constants::DBusService, Constants::DBusPath, "",
                             QDBusConnection::systemBus(), parent)
{
}

SmackLabelIf::~SmackLabelIf()
{

}

QDBusPendingReply<QString> SmackLabelIf::getConnectionLabel(const QString &service)
{
    QList<QVariant> argumentList;
    argumentList << qVariantFromValue(service);
    return asyncCallWithArgumentList(QLatin1String("GetConnectionLabel"), argumentList);
}
