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
#include "aegiscrypto.h"

#include <QtCore/QByteArray>
#include <QtCore/QDataStream>
#include <QtCore/QFile>
#include <QtCore/QtDebug>

// the file into which the settings will be stored
const char * const filename = "/tmp/mssf-demo.storage";
// Token used for encrypting data, Use NULL to signify the use of ApplicationID
const char * const encryptToken = NULL;

ConfigWriter::ConfigWriter()
{
}

ConfigWriter::~ConfigWriter()
{
}

bool ConfigWriter::writeConfig(const Configuration &config)
{
    // use a file in the normal file system
    QFile storageFile(filename);
    if (!storageFile.open(QIODevice::ReadWrite | QIODevice::Truncate))
    {
        qDebug() << "Failed to open the settings file: " << storageFile.error();
        return false;
    }

    QDataStream fileStream(&storageFile);
    // Serialize the configuration to aa array
    QByteArray data;
    QDataStream structStream(&data, QIODevice::WriteOnly);
    structStream << config;

    //write the encrypted data to file
    fileStream << AegisCrypto::encryptData(data, encryptToken);
    return true;
}

Configuration ConfigWriter::readConfig()
{
    QFile storageFile(filename);
    if (!storageFile.open(QIODevice::ReadOnly))
    {
        qDebug() << "Failed to open the settings file: "  << storageFile.error();
        return Configuration();
    }

    QDataStream fileStream(&storageFile);
    QByteArray data;
    fileStream >> data;

    if (data.isEmpty())
    {
        qDebug() << "Failed to read the data from file.";
        return Configuration();
    }

    QDataStream byteStream(AegisCrypto::decryptData(data, encryptToken));
    // de-serialize the data
    Configuration config;
    byteStream >> config;

    return config;
}
