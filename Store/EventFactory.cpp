#include "EventFactory.h"

#include <QEvent>
#include <QMetaEnum>

#include <ctime>
#include <chrono>

namespace
{
    QString epochToString( qint64 _epoch )
    {
        const std::chrono::system_clock::duration duration = std::chrono::milliseconds( _epoch );
        std::chrono::high_resolution_clock::time_point time( duration );
        std::chrono::milliseconds ms = std::chrono::duration_cast< std::chrono::milliseconds >( time.time_since_epoch() );
        std::chrono::seconds s = std::chrono::duration_cast< std::chrono::seconds >( ms );

        std::time_t resultTime = s.count();

        char buffer[ 100 ];
        std::strftime( buffer, sizeof( buffer ), "%T.%%1\n%e/%m/%C", std::localtime( &resultTime ) );

        return QString { buffer }.arg( ms.count() % 1000 );
    }
}

EventFactory& EventFactory::instance()
{
    static EventFactory self;

    return self;
}

EventFactory::~EventFactory()
{
    m_dictionary.clear();
}

Event* EventFactory::create( qint64 _epoch, qint32 _type, const QString& _target, const QString& _description )
{
    QString dateTimeString = epochToString( _epoch );

    static int eventEnumIndex = QEvent::staticMetaObject.indexOfEnumerator( "Type" );

    QString typeString = QEvent::staticMetaObject.enumerator( eventEnumIndex ).valueToKey( _type );

    if ( typeString.isEmpty() )
        typeString = QString { ( _type < QEvent::User ) ? QStringLiteral( "Undefined(%1)" ) : QStringLiteral( "User(%1)" ) }.arg( _type );

    return new Event { _epoch, _type, registerString( _target ), registerString( _description ), registerString( dateTimeString ), registerString( typeString ) };
}

QString EventFactory::registerString( const QString& _value )
{
    auto it = m_dictionary.find( _value );
    if ( it != m_dictionary.end() )
        return *it;
    else
        return *m_dictionary.insert( _value );
}

void EventFactory::clear()
{
    m_dictionary.clear();
}
