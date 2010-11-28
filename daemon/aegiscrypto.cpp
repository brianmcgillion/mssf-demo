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

#include "aegiscrypto.h"

#include <aegis_crypto.h>
using namespace aegis;

#include <QtCore/QtDebug>

//! seperator that is used between origional message and signature
const char SignatureSeperator = '|';

AegisCrypto::AegisCrypto()
{
}

AegisCrypto::~AegisCrypto()
{
}

bool AegisCrypto::initialize()
{
    return static_cast<bool>(aegis_crypto_init());
}

QByteArray AegisCrypto::encryptData(const QByteArray &clearText, const char *token)
{
    if (clearText.length() <= 0)
        return QByteArray();

    RAWDATA_PTR cipherText = NULL;
    size_t cipherLength = 0;

    if (aegis_crypto_encrypt(clearText.data(), clearText.length(), token, &cipherText, &cipherLength) != aegis_crypto_ok)
    {
        aegis_crypto_free(cipherText);
        qDebug("Failed to encrypt data: %s", aegis_crypto_last_error_str());
        return QByteArray();
    }

    QByteArray encrypted((char *)cipherText, cipherLength);
    aegis_crypto_free(cipherText);
    return encrypted;
}

QByteArray AegisCrypto::decryptData(const QByteArray &cipherText, const char *token)
{
    if (cipherText.length() <= 0)
        return QByteArray();

    RAWDATA_PTR clearText = NULL;
    size_t length = 0;

    if (aegis_crypto_decrypt(cipherText.data(), cipherText.length(), token, &clearText, &length) != aegis_crypto_ok)
    {
        aegis_crypto_free(clearText);
        qDebug("Failed to decrypt data: %s", aegis_crypto_last_error_str());
        return QByteArray();
    }

    QByteArray decrypted((char *)clearText, length);
    aegis_crypto_free(clearText);
    return decrypted;
}

QByteArray AegisCrypto::signData(const QByteArray &data, const char *token)
{
    aegis_signature_t signature;
    //First sign the data
    if (aegis_crypto_sign(data.data(), data.length(), token, &signature) != aegis_crypto_ok)
    {
        qDebug("Failed to sign data: %s", aegis_crypto_last_error_str());
        return QByteArray();
    }

    //Then create a string Representation of if
    char *signatureAsString = NULL;
    aegis_crypto_signature_to_string(&signature, aegis_as_base64, token, &signatureAsString);

    //create a data block that contains the origional data with the signature appended to it
    QByteArray encodedSignature(data);
    encodedSignature.append(SignatureSeperator);
    encodedSignature.append(signatureAsString);

    aegis_crypto_free(signatureAsString);
    return encodedSignature;
}

QByteArray AegisCrypto::validateSignatureAndSplit(const QByteArray &signedData)
{
    aegis_signature_t signature;
    aegis_system_mode_t mode;
    char *tokenName = NULL;
    int sepPosition = signedData.lastIndexOf(SignatureSeperator);

    if (aegis_crypto_string_to_signature(signedData.mid(sepPosition + 1).data(), &signature,
                                         &tokenName) != aegis_crypto_ok)
    {
        aegis_crypto_free(tokenName);
        qDebug("Failed to convert string to signature: %s", aegis_crypto_last_error_str());
        return QByteArray();
    }

    QByteArray message = signedData.left(sepPosition);
    if (aegis_crypto_verify(&signature, tokenName, message.data(), message.length(),
                            &mode) != aegis_crypto_ok)
    {
        aegis_crypto_free(tokenName);
        qDebug("Failed To validate Signature: %s", aegis_crypto_last_error_str());
        return QByteArray();
    }

    aegis_crypto_free(tokenName);
    return message;
}
