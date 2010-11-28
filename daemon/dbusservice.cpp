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

#include "dbusservice.h"
#include "engine.h"
#include "mssf-common.h"

//access libcreds2
#include <DBusContextAccessManager>

#include <QtCore/QString>
#include <QtCore/QLatin1String>

DBusService::DBusService(Engine *parent)
    :   QObject(parent),
      engine(parent)
{
}

DBusService::~DBusService()
{
}

bool DBusService::setState(int state)
{
    if (state >= Mssf::Undefined)
        sendErrorReply(QDBusError::NotSupported, "Unknown state requested");

    QString credential;
    switch ((Mssf::State)state)
    {
    case Mssf::Clean:
        credential = QLatin1String("mssf-demo::Clean_State");
        break;
    case Mssf::Stopped:
        credential = QLatin1String("mssf-demo::Stop_State");
        break;
    default:
        break;
    }

    qDebug("The clients id is (%d)", (int)DBusContextAccessManager::getClientPID(*this));

    if (!credential.isEmpty())
    {
        //not all states changes require a token
        QString errorString;
        if (!DBusContextAccessManager::hasClientCredential(*this, credential, &errorString))
        {
            qDebug() << "Failed to validate credential: " << errorString;
            sendErrorReply(QDBusError::AccessDenied, "Caller does not possess the correct credentials");
            return false;
        }
    }

    return engine->setState(state);
}
