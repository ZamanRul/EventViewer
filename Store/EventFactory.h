#ifndef EVENTFACTORY_H
#define EVENTFACTORY_H

#include "Event.h"

#include <QSet>

class EventFactory
{

public:

    static EventFactory& instance();

public:

    ~EventFactory();

    Event* create( qint64 _epoch, qint32 _type, const QString& _target, const QString& _description );

    void clear();

private:

    EventFactory() = default;
    EventFactory( const EventFactory& ) = delete;
    EventFactory( EventFactory&& ) = delete;
    EventFactory& operator=( const EventFactory& ) = delete;
    EventFactory& operator=( EventFactory&& ) = delete;

    QString registerString( const QString& _value );

private:

    QSet< QString > m_dictionary;
};

#endif // EVENTFACTORY_H
