/*
 * This file is part of MSSF
 *
 * Copyright (C) 2010 Brian McGillion
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * version 2.1 as published by the Free Software Foundation.
 *
 * This library is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
 * 02110-1301 USA
 *
 * Author: Brian McGillion <brian.mcgillion@symbio.com>
 */

#include "engine.h"
#include "engineconfigs.h"
#include "dbusservice.h"
#include "dbusserviceifadaptor.h"
#include "mssf-common.h"
#include "configwriter.h"

#include <QtNetwork/QLocalSocket>

Engine::Engine(QObject *parent)
    :  QObject(parent),
      dbusService(NULL),
      sockServer(NULL),
      storage(NULL)
{
    qRegisterMetaType<Mssf::State>("Mssf::State");
}

Engine::~Engine()
{
    delete storage; storage = NULL;
}

bool Engine::initialize()
{
    config.setName("MainEngine");
    config.setType(EngineSettings::Category);
    config.insertField(EngineSettings::State, QVariant(static_cast<int>(Mssf::Stopped)));

    storage = new ConfigWriter();
    Configuration storedConfig = storage->readConfig();

    //combine the stored config
    config.insertFields(storedConfig.fields());

    sockServer = new QLocalServer(this);
    // clean up the old instance if it exists.
    sockServer->removeServer(Mssf::serverName);

    if (!sockServer->listen(Mssf::serverName))
    {
        qCritical() << "Falied to start the LocalServer: " << sockServer->errorString();
        return false;
    }

    connect(sockServer, SIGNAL(newConnection()), this, SLOT(handleConnection()));
    return startDBus();
}

bool Engine::setState(int state)
{
    if (state >= Mssf::Undefined)
        return false;

    config.insertField(EngineSettings::State, QVariant(static_cast<int>(state)));
    storage->writeConfig(config);
    return true;
}

bool Engine::startDBus()
{
    if (dbusService)
        return true;

    dbusService = new DBusService(this);
    new DBusServiceIfAdaptor(dbusService);

    QDBusConnection connection = QDBusConnection::systemBus();
    if (!connection.registerObject("/", dbusService))
    {
        qCritical() << "Failed to register Object for DBus: " << connection.lastError().message();
        return false;
    }

    if (!connection.registerService("com.meego.mssf"))
    {
        qCritical() << "Failed to register for DBus Service: " << connection.lastError().message();
        return false;
    }

    return true;
}

void Engine::handleConnection()
{
    QLocalSocket *sockClient = sockServer->nextPendingConnection();
    connect(sockClient, SIGNAL(disconnected()), sockClient, SLOT(deleteLater()));

    bool result = false;
    qint32 state = Mssf::Undefined;

    if (sockClient->waitForReadyRead())
    {
        QDataStream stream(sockClient);
        quint8 version;
        stream >> version;

        if (version == 1)
        {
            // read the state from the client and attempt to set it
            stream >> state;
            result = setState(state);
        }
    }
    else
    {
        qDebug() << "There is no data available on the socket ??";
    }

    // Now write the result back to the client
    QByteArray data;
    QDataStream replyStream(&data, QIODevice::WriteOnly);
    replyStream << (quint8)1; // version
    replyStream << (qint32)state;
    replyStream << (bool)(result);

    sockClient->write(data);
    sockClient->flush();
    sockClient->disconnectFromServer();
}
