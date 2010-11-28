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

#ifndef AEGISCRYPTO_H
#define AEGISCRYPTO_H

#include <QtCore/QByteArray>

class AegisCrypto
{
public:

    /*!
      * \brief Default Constructor
      */
    AegisCrypto();

    /*!
      * \Destructor
      */
    ~AegisCrypto();

    /*!
      * \brief Initialize the AegisCrypto.
      */
    static bool initialize();

    /*!
      * \brief Cryptographically sign some data and use the optional token to provide shared access.
      * \param data The data that is to be signed
      * \param token The shared token to use for the signing
      * \returns On success the signed data is returned, on error an empty QByteArray() will be returned-
      * The signed data that is returned on success has the following format:
      * [ data|signature-tokenName ], notice the use of the (|) that is used to seperate the origional
      * data from the signature.  If a token is used its name is appended to the signature after the (-).
      * \sa aegis::crypto
      */
    static QByteArray signData(const QByteArray &data, const char *token);

    /*!
      * \brief Verify that the signature on a signed piece of data is correct.
      * \param signedData THe data and the signature that are to be tested
      * \returns true if the validation is successful, false otherwise
      * This method expects to get the signed data in the following format:
      * [ data|signature-tokenName ], notice the use of the (|) that is used to seperate the origional
      * data from the signature.  The -tokenName is optional and will have been specified at signing time.
      *
      * \sa aegis::crypto
      */
    static QByteArray validateSignatureAndSplit(const QByteArray &signedData);

    /*!
      * \brief Encrypt the clear text and use the optional token for reference.
      * \param data The origional message that is to be encrypted.
      * \param token The optional token to use for referencing the encrypted data.
      * \returns The encrypted data on success or an empty QByteArray() on failure.
      */
    static QByteArray encryptData(const QByteArray &data, const char *token);

    /*!
      * \brief decrypt a given message using an optional token as reference
      * \param data The encrypted message that is to be decoded.
      * \param token An optional token to use as a reference
      * \returns The deciphered data on success, an empty QByteArray() on failure.
      */
    static QByteArray decryptData(const QByteArray &data, const char *token);
};

#endif // AEGISCRYPTO_H
