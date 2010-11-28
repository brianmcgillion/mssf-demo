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

#include "configwriter.h"
#include "engineconfigs.h"
#include "aegisstorage.h"

#include <QtCore/QByteArray>
#include <QtCore/QDataStream>
#include <QtCore/QtDebug>

//! The storage file location used for the standard configuration settings
const char * const MssfStorageName = "MssfStorage";
//! The file path that is used within aegis crypto to store these settings.
const char * const filename = "/tmp/mssf-demo.storage";

ConfigWriter::ConfigWriter()
{
}

ConfigWriter::~ConfigWriter()
{
}

bool ConfigWriter::writeConfig(const Configuration &config)
{
    // Serialize the configuration to an array
    QByteArray data;
    QDataStream structStream(&data, QIODevice::WriteOnly);
    structStream << config;

    // using NULL as a token means that the APPLICATION ID is used internally
    return AegisStorage::aegisStorageWrite(MssfStorageName, filename, NULL, data);
}

Configuration ConfigWriter::readConfig()
{
    QByteArray data = AegisStorage::aegisStorageGet(MssfStorageName, filename, NULL);

    if (data.isEmpty())
        return Configuration();

    // de-serialize the data
    QDataStream byteStream(data);
    Configuration config;
    byteStream >> config;

    return config;
}
