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

/*!
  * \file configurations.h
  * \class Configurations
  * \brief This is the in memory representation of a set of data that is used with in the application.
  */

#ifndef CONFIGURATIONS_H
#define CONFIGURATIONS_H

#include <QtCore/QSharedDataPointer>
#include <QtCore/QString>
#include <QtCore/QVariant>

class ConfigurationData;

class Configuration
{
public:

    /*!
      * \brief Default constructor
      */
    Configuration();

    /*!
      * \brief Constructor
      * \param type The type of configuration to create.
      * \param name The optional name to assign to the configuration.
      */
    explicit Configuration(const QString &type, const QString &name = QString());

    /*!
      * \brief Copy constructor
      * \param other The other data to copy
      */
    Configuration(const Configuration &other);

    /*!
      * \brief Destructor
      */
    ~Configuration();

    /*!
      * \brief Assignment operator
      * \param other The other configuration to assigne to this
      * \returns A reference to this configuration
      */
    Configuration& operator=(const Configuration &other);

    /*!
      * \brief The name of this configuration
      * \returns The configuration name
      */
    QString name() const;

    /*!
      * \brief Set the name of this configuration.
      * \param name The name to be used
      */
    void setName(const QString &name);

    /*!
      * \brief The type of configuration that is cureated here.
      * \returns The type
      */
    QString type() const;

    /*!
      * \brief Set the type of this configuration
      * \param type The name of the type to be used.
      */
    void setType(const QString &type);

    /*!
      * \brief Get the value associated with a particular setting
      * \param field The setting name
      * \returns The value if it exists or a, Qvariant() if it does not.
      */
    QVariant value(const QString &field) const;

    /*!
      * \brief insert or overwrite a setting
      * \param field The filed to create or update
      * \param value The value to assign to the field
      */
    void insertField(const QString &field, const QVariant &value);

    /*!
      * \brief insert or overwrite a group of settings
      * \param fields The fields to add / overwrite
      */
    void insertFields(const QVariantHash &fields);

    /*!
      * \brief Remove a field and its associated data.
      * \param field The field to be removed
      */
    void removeField(const QString &field);

    /*!
      * \brief Determine if a particular setting is stored in this configuration
      */
    bool hasField(const QString &field) const;

    /*!
      * \brief List all of the fields and their data
      * \param The hash that contains all the settings
      */
    QVariantHash fields() const;

    /*!
      * \brief Create or overwrite all the settings stored in this configuration
      * \param fields The new data to store.
      */
    void setFields(const QVariantHash &fields);

private:
    //! The actual data that is managed
    QSharedDataPointer<ConfigurationData> data;
};

/*!
  * \brief Serialization routine for the data.
  * \param stream The stream that is being written to.
  * \param configuration The configuration that is being serialized
  * \returns a reference to the stream
  */
QDataStream& operator<<(QDataStream& stream, const Configuration &configuration);

/*!
  * \brief Serialization routine for the data.
  * \param stream The stream that is being read from.
  * \param configuration The configuration that is being populated with data.
  * \returns a reference to the stream
  */
QDataStream& operator>>(QDataStream& stream, Configuration &configuration);

// declare as metatype
Q_DECLARE_METATYPE(Configuration)

#endif // CONFIGURATIONS_H
