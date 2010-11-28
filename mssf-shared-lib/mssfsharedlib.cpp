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

#include "mssfsharedlib.h"
#include <libcreds2-qt/CredentialsManager>
#include <QtCore/QString>
#include <QtCore/QtDebug>

MssfSharedLib::MssfSharedLib()
{
}

MssfSharedLib::~MssfSharedLib()
{

}

bool MssfSharedLib::clientMethod()
{
    QString errorString;
    if (!CredentialsManager::hasProcessCredential(0, "mssf-demo::ClientLibraryAccess", &errorString))
    {
        qDebug() << "Failed to validate credential for client method: " << errorString;
        return false;
    }

    commonInitialization();
    qDebug() << "Client Verified, doing client specific work ....";
    commonFinilazation();

    return true;
}

bool MssfSharedLib::daemonMethod()
{
    QString errorString;
    if (!CredentialsManager::hasProcessCredential(0, "mssf-demo::DaemonLibraryAccess", &errorString))
    {
        qDebug() << "Failed to validate credential for daemon method: " << errorString;
        return false;
    }

    commonInitialization();
    qDebug() << "Daemon Verified, doing daemon specific work ....";
    commonFinilazation();

    return true;
}

void MssfSharedLib::commonInitialization()
{
    qDebug() << "Calling some initialization routines.";
}

void MssfSharedLib::commonFinilazation()
{
    qDebug() << "Calling some finialization routines.";
}
