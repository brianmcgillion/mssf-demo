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

#ifndef AEGISSTORAGE_H
#define AEGISSTORAGE_H

#include <QtCore/QString>
#include <QtCore/QByteArray>
#include <QtCore/QStringList>

#include <aegis_storage.h>
#include <aegis_crypto.h>
using namespace aegis;

class AegisStorage
{
public:

    /*!
      * \brief Constrctor
      */
    AegisStorage();

    /*!
      * \brief Destructor
      */
    ~AegisStorage();

    /*!
      * \brief Write data to a storage location.
      * \param storageName The name of the storage area to access
      * \param storagePath The file in which the data is stored.
      * \param token The token that is required to access the storage area
      * \returns true on success, false otherwise.
      */
    static bool aegisStorageWrite(const char *storageName, const char *storagePath, const char *token, const QByteArray &data);

    /*!
      * \brief This is an overloaded method provided for convenience
      */
    static bool aegisStorageWrite(const QString &storageName, const QString &storagePath, const char *token, const QByteArray &data);

    /*!
      * \brief Read the data that is stored in a file in the storage area.
      * \param storageName The name of the storage area to access
      * \param storagePath The file in which the data is stored.
      * \param token The token that is required to access the storage area
      * \returns the data if successful, QByteArray() otherwise
      */
    static QByteArray aegisStorageGet(const char *storageName, const char *storagePath, const char *token);

    /*!
      * \brief This is an overloaded method provided for convenience
      */
    static QByteArray aegisStorageGet(const QString &storageName, const QString &storagePath, const char *token);

    /*!
      * \brief Get a list of files that are currently stored in the storage area
      * \param storageName The storage area to read from.
      * \param mask A RegExp capable mask to narrow the search
      * \param token The token that is required to access the storage area
      * \returns The list of files in the storage area if successful, or QStringList() otherwise
      */
    static QStringList aegisFileList(const char *storageName, const QString &mask, const char *token);

    /*!
      * \brief Remove all the files in a storage area
      * \param storageName The Storage name to access
      * \param token The token that is required to access the storage.
      * \returns true if successful, false otherwise
      */
    static bool aegisRemoveAllFiles(const char *storageName, const char *token);
};

#endif // AEGISSTORAGE_H
