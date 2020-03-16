#include "Event.h"

Event::Event( qint64 _epoch, qint32 _type, const QString& _target, const QString& _description, const QString& _dateTimeString, const QString& _typeString ) :
    m_epoch { _epoch },
    m_dateTimeString { _dateTimeString },
    m_type { _type },
    m_typeString { _typeString },
    m_target { _target },
    m_description { _description }
{}

qint64 Event::epoch() const
{
    return m_epoch;
}

QString Event::dateTime() const
{
    return m_dateTimeString;
}

qint32 Event::type() const
{
    return m_type;
}

QString Event::typeName() const
{
    return m_typeString;
}

QString Event::target() const
{
    return m_target;
}

QString Event::description() const
{
    return m_description;
}
