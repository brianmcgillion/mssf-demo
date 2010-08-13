/*
  * Copyright (C) 2006-2010 Nokia Corporation.
  *
  * This file is part of devicelock
  *
  * Authors: Brian McGillion <brian.mcgillion@symbio.com>,
  * 	     Denis Mingulov  <denis.mingulov@symbio.com>
  *
  * This program is free software; you can redistribute it and/or
  * modify it under the terms of the GNU General Public License
  * version 2 as published by the Free Software Foundation.
  *
  * This program is distributed in the hope that it will be useful, but
  * WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  * General Public License for more details.
  *
  * You should have received a copy of the GNU General Public License
  * along with this program; if not, write to the Free Software
  * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
  * 02110-1301 USA
  *
  */

#ifndef LIBCREDS2QT_GLOBAL_H
#define LIBCREDS2QT_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(LIBCREDSQT_LIBRARY)
#  define LIBCREDS2QTSHARED_EXPORT Q_DECL_EXPORT
#else
#  define LIBCREDS2QTSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // LIBCREDSQT_GLOBAL_H
