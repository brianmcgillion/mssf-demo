/*
  * Copyright (C) 2006-2010 Nokia Corporation.
  *
  * This file is part of devicelock
  *
  * Authors: Brian McGillion <brian.mcgillion@symbio.com>,
  * 	     Denis Mingulov  <denis.mingulov@symbio.com>
  *
  * This program is free software; you can redistribute it and/or
  * modify it under the terms of the GNU General Public License
  * version 2 as published by the Free Software Foundation.
  *
  * This program is distributed in the hope that it will be useful, but
  * WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  * General Public License for more details.
  *
  * You should have received a copy of the GNU General Public License
  * along with this program; if not, write to the Free Software
  * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
  * 02110-1301 USA
  *
  */

#include "dbuscontextaccessmanager.h"
#include "credentialsmanager.h"

#include <QDBusMessage>
#include <QDBusConnection>
#include <QDBusConnectionInterface>


DBusContextAccessManager::DBusContextAccessManager()
{
}

DBusContextAccessManager::~DBusContextAccessManager()
{

}

bool DBusContextAccessManager::hasClientCredential(const QDBusContext &context, const QString &credential, QString *errorString)
{
    return CredentialsManager::hasProcessCredential(getClientPID(context), credential, errorString);
}

pid_t DBusContextAccessManager::getClientPID(const QDBusContext &context)
{
    QString serviceName = context.message().service();
    return context.connection().interface()->servicePid(serviceName).value();
}

uid_t DBusContextAccessManager::getClientUID(const QDBusContext &context)
{
    QString serviceName = context.message().service();
    return context.connection().interface()->serviceUid(serviceName).value();
}
