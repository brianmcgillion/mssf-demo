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

#ifndef MSSFSHAREDLIB_GLOBAL_H
#define MSSFSHAREDLIB_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(LIBMSSF_SHARED_LIBRARY)
#  define LIBMSSFSHARED_EXPORT Q_DECL_EXPORT
#else
#  define LIBMSSFSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // MSSFSHAREDLIB_GLOBAL_H
