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

#ifndef DBUSSERVICE_H
#define DBUSSERVICE_H

#include <QtCore/QObject>
#include <QtDBus/QDBusContext>

class Engine;

class DBusService : public QObject, protected QDBusContext
{
    Q_OBJECT
    Q_DISABLE_COPY(DBusService);

public:

    /*!
      * \brief Default constructor
      * \param parent The parent Object.
      */
    explicit DBusService(Engine *parent = 0);

    /*!
      * \brief Destructor
      */
    ~DBusService();

signals:

    /*!
      * \brief Notify any listners that the state of the application has changed.
      */
    void stateChanged(int state);

public slots:

    /*!
      * \brief Set the state of the application.
      * \param state The state to set
      * \returns true if set, false otherwise
      */
    bool setState(int state);

private:
    //! The main engine to hand off the commands to..
    Engine *engine;
};

#endif // DBUSSERVICE_H
