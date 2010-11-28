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

#include "configuration.h"
#include "configuration_p.h"

Configuration::Configuration()
    : data(new ConfigurationData)
{
}

Configuration::Configuration(const QString &type, const QString &name)
    : data(new ConfigurationData)
{
    setType(type);
    setName(name);
}

Configuration::Configuration(const Configuration &other)
    : data(other.data)
{
}

Configuration::~Configuration()
{
}

Configuration& Configuration::operator=(const Configuration &other)
{
    data = other.data;
    return *this;
}

QVariant Configuration::value(const QString &name) const
{
    return data->fields.value(name, QVariant());
}

QString Configuration::name() const
{
    return data->name;
}

QString Configuration::type() const
{
    return data->type;
}

void Configuration::setName(const QString &name)
{
    data->name = name;
}

void Configuration::setType(const QString &type)
{
    data->type = type;
}

void Configuration::insertField(const QString &field, const QVariant &value)
{
    if (value.isValid())
        data->fields.insert(field, value);
}

void Configuration::insertFields(const QVariantHash &fields)
{
    QVariantHash::ConstIterator it;
    for (it = fields.begin(); it != fields.end(); it++)
        data->fields.insert(it.key(), it.value());
}

void Configuration::removeField(const QString &field)
{
    data->fields.remove(field);
}

bool Configuration::hasField(const QString &field) const
{
    return data->fields.contains(field);
}

QVariantHash Configuration::fields() const
{
    return data->fields;
}

void Configuration::setFields(const QVariantHash &fields)
{
    data->fields = fields;
}

QDataStream& operator<<(QDataStream& stream, const Configuration &configuration)
{
    return stream << quint8(1)
                  << configuration.name()
                  << configuration.type()
                  << configuration.fields();
}

QDataStream& operator>>(QDataStream &stream, Configuration &configuration)
{
    configuration = Configuration();
    quint8 version;
    stream >> version;
    if (version == 1)
    {
        QString name;
        QString type;
        QVariantHash fields;
        stream >> name >> type >> fields;
        configuration.setName(name);
        configuration.setType(type);
        configuration.setFields(fields);
    }
    else
    {
        stream.setStatus(QDataStream::ReadCorruptData);
    }

    return stream;
}
