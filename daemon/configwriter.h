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

#ifndef CONFIGWRITER_H
#define CONFIGWRITER_H

#include "configuration.h"

class ConfigWriter
{

public:

    /*!
      * \brief Constructor
      */
    explicit ConfigWriter();

    /*!
      * \brief Destructor
      */
    ~ConfigWriter();

    /*!
      * \brief write a configuration to the storage area
      * \param config The configuration to be write
      * \returns true if the data could be written, false otherwise
      */
    bool writeConfig(const Configuration &config);

    /*!
      * \brief Read a configuration from the storage area.
      * \returns The settings if they exist, Configuration() otherwise.
      */
    Configuration readConfig();
};

#endif // CONFIGWRITER_H
