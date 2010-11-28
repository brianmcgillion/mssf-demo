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

#ifndef MSSFSHAREDLIB_H
#define MSSFSHAREDLIB_H

#include "mssf-shared-lib_global.h"

class LIBMSSFSHARED_EXPORT MssfSharedLib
{
public:

    /*!
      * \brief Constructor
      */
    MssfSharedLib();

    /*!
      * \brief Destructor
      */
    ~MssfSharedLib();

    /*!
      * \brief A method that is only accessible from the client with the correct credentials.
      * \returns true if the method succeeds, false otherwise
      */
    bool clientMethod();

    /*!
      * \brief A method that is callable only by the daemon with the correct credentials
      * \returns true on success, false otherwise
      */
    bool daemonMethod();

private:

    /*!
      * \brief Some initialization method that is common to users of the library
      */
    void commonInitialization();

    /*!
      * \brief Some finalization routine that is common to all users of the library.
      */
    void commonFinilazation();
};

#endif // MSSFSHAREDLIB_H
