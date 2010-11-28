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

#include "client.h"
#include "serverdbus.h"
#include "../daemon/aegiscrypto.h"
#include "../daemon/mssf-common.h"

#include <QtCore/QDataStream>

Client::Client(QObject *parent)
    :   QObject(parent),
      clientSock(NULL),
      dbusClient(NULL)
{
}

Client::~Client()
{
}

void Client::run()
{
    AegisCrypto::initialize();

    // Connect via Dbus and set the state
    // call all usable states
    dbusClient = new ServerDBus(this);
    dbusClient->setState(Mssf::Running);
    dbusClient->setState(Mssf::Stopped);
    dbusClient->setState(Mssf::ReStart);
    dbusClient->setState(Mssf::Clean);

    // perform a write using the Socket connection
    clientSock = new QLocalSocket(this);
    connect(clientSock, SIGNAL(readyRead()), this, SLOT(readSocket()));
    clientSock->connectToServer(Mssf::serverName);

    QByteArray data;
    QDataStream stream(&data, QIODevice::WriteOnly);
    stream << (quint8)1; // version
    stream << static_cast<qint32>(Mssf::Running);

    clientSock->write(data);
    clientSock->flush();
}

void Client::readSocket()
{
    if (clientSock->bytesAvailable() > 0)
    {
        QByteArray data = clientSock->readAll();
        if (data.isEmpty())
        {
            qDebug() << "Failed to read the data from socket.";
            return;
        }

        QDataStream byteStream(AegisCrypto::decryptData(data, Mssf::tokenName));

        quint8 version;
        byteStream >> version;
        if (version == 1)
        {
            bool success;
            qint32 state;
            byteStream >> state;
            byteStream >> success;
            qDebug() << "Received response from socket for state (" << state << "): " << success;
        }
    }
}
