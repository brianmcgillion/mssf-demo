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

#include <QtCore/QSharedPointer>
#include <QtCore/QVector>
#include <QtCore/QRegExp>
#include <QtCore/QtDebug>

#include "aegisstorage.h"

AegisStorage::AegisStorage()
{
}

AegisStorage::~AegisStorage()
{
}

bool AegisStorage::aegisStorageWrite(const QString &storageName, const QString &storagePath,
                                     const char *token, const QByteArray &data)
{
    return AegisStorage::aegisStorageWrite(storageName.toUtf8().constData(),
                                           storagePath.toUtf8().constData(), token, data);
}

bool AegisStorage::aegisStorageWrite(const char *storageName, const char *storagePath,
                                     const char *token, const QByteArray &data)
{
    if (!storageName || !storagePath)
    {
        qDebug("Invalid Storage Name or path");
        return false;
    }

    QSharedPointer<storage> aegisStorage(new storage(storageName, token, storage::vis_private, storage::prot_encrypted));

    if (aegisStorage->put_file(storagePath, (void *)data.data(), data.length()) != 0)
    {
        qDebug("Failed To create or retrieve an Aegis-Storage location: %s", aegis_crypto_last_error_str());
        return false;
    }

    aegisStorage->commit();
    return true;
}

QByteArray AegisStorage::aegisStorageGet(const QString &storageName, const QString &storagePath, const char *token)
{
    return aegisStorageGet(storageName.toUtf8().constData(), storagePath.toUtf8().constData(), token);
}

QByteArray AegisStorage::aegisStorageGet(const char *storageName, const char *storagePath, const char *token)
{
    if (!storageName || !storagePath)
    {
        qDebug("Invalid Storage Name or path");
        return false;
    }

    QSharedPointer<storage> aegisStorage(new storage(storageName, token, storage::vis_private, storage::prot_encrypted));

    RAWDATA_PTR storedData = NULL;
    size_t cipherLength = 0;

    if (aegisStorage->get_file(storagePath, &storedData, &cipherLength) != 0)
    {
        aegisStorage->release_buffer(storedData);
        qDebug("Failed To get data from file: %s", aegis_crypto_last_error_str());
        return false;
    }

    QByteArray retrievedData((char *)storedData, cipherLength);
    aegisStorage->release_buffer(storedData);

    return retrievedData;
}

QStringList AegisStorage::aegisFileList(const char *storageName, const QString &mask, const char *token)
{
    if (!storageName)
    {
        qDebug( "Invalid Storage Name");
        return QStringList();
    }

    qDebug() << "Get file list for " << storageName << ", mask " <<  mask;

    QSharedPointer<storage> aegisStorage(new storage(storageName, token, storage::vis_private, storage::prot_encrypted));

    aegis::storage::stringlist list;
    size_t total = aegisStorage->get_files(list);
    if (total <= 0)
    {
        qDebug("No files found");
        return QStringList();
    }

    QList<const char *> fullList = QList<const char *>::fromVector(QVector<const char *>::fromStdVector(list));

    QStringList resultList;

    QRegExp rx(mask);
    rx.setPatternSyntax(QRegExp::Wildcard);

    foreach(const char *sz, fullList)
    {
        QString file(sz);
        qDebug() << "Filtering for the file " << file;

        if (mask.isEmpty() || rx.exactMatch(file))
            resultList.append(file);
    }

    // free the memory
    aegisStorage->release(list);
    qDebug("Found %d files", resultList.count());

    return resultList;
}

bool AegisStorage::aegisRemoveAllFiles(const char *storageName, const char *token)
{
    if (!storageName)
    {
        qDebug( "Invalid Storage Name");
        return false;
    }

    storage aegisStorage(storageName, token, storage::vis_private, storage::prot_encrypted);
    return aegisStorage.remove_all_files();
}
