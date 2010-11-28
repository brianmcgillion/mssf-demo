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
  * \file configurationdata_p.h
  * \class ConfigurationData
  * \brief This is the actual data associated with a Configuration.
  */

#ifndef CONFIGURATIONSDATA_P_H
#define CONFIGURATIONSDATA_P_H

#include "configuration.h"

#include <QtCore/QSharedData>
#include <QtCore/QHash>
#include <QtCore/QVariant>
#include <QtCore/QString>

class ConfigurationData : public QSharedData
{
public:

    /*!
      * \brief Default constructor
      */
    ConfigurationData()
        : QSharedData(),
          name(QString()),
          type(QString())
    {
    }

    /*!
      * \brief Copy constructor
      * \param other The other data to copy
      */
    ConfigurationData(const ConfigurationData &other)
        : QSharedData(other),
          name(other.name),
          type(other.type),
          fields(other.fields)
    {
    }

    /*!
      * \brief Destructor
      */
    ~ConfigurationData()
    {
    }

    //! The name of this configuration
    QString name;
    //! The type of this configuration
    QString type;
    //! The main data that we are working with
    QVariantHash fields;
};

#endif // CONFIGURATIONSDATA_P_H
