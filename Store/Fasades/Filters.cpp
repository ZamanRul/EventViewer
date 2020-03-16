#include "Filters.h"

#include <QDebug>

#ifdef PERF_LOGS
    #include "Utility/PerformanceLogger.h"
#endif

Filters::Filters() :
    m_running { false },
    m_eventTypes { new EventTypes { } },
    m_filteredEventTypes { new FilteredEventTypes { } }
{
    if ( m_filteredEventTypes.isNull() )
        qCritical().nospace().noquote() << "ERROR: Filtered event's types list is empty";
    else
        m_filteredEventTypes->setSourceModel( m_eventTypes.get() );
}

bool Filters::running() const
{
    return m_running;
}

void Filters::setRunning( bool _running )
{
    if ( m_running != _running )
    {
        m_running = _running;

        emit runningChanged();
    }
}

QObject* Filters::filteredEventTypes() const
{
    return m_filteredEventTypes.get();
}

void Filters::registerData( QSharedPointer< ProcessedData > _data )
{
    BENCHMARK( "Filters::registerData()" )

    if ( _data.isNull() )
    {
        qCritical().nospace().noquote() << "ERROR: Cannot operate on null data";
        return;
    }

    if ( m_eventTypes.isNull() )
    {
        qCritical().nospace().noquote() << "ERROR: Event's types list is empty";
        return;
    }

    if ( m_filteredEventTypes.isNull() )
    {
        qCritical().nospace().noquote() << "ERROR: Filtered event's types list is empty";
        return;
    }

    setRunning( true );

    m_eventTypes->registerData( _data->eventTypesOccurrences() );

    m_filteredEventTypes->sort( 0 );

    setRunning( false );
}

void Filters::filterByTime( QSharedPointer< ProcessedData > _data )
{
    BENCHMARK( "Filters::filterByTime()" )

    if ( _data.isNull() )
    {
        qCritical().nospace().noquote() << "ERROR: Cannot operate on null data";
        return;
    }

    if ( m_eventTypes.isNull() )
    {
        qCritical().nospace().noquote() << "ERROR: Event's types list is empty";
        return;
    }

    if ( m_filteredEventTypes.isNull() )
    {
        qCritical().nospace().noquote() << "ERROR: Filtered event's types list is empty";
        return;
    }

    setRunning( true );

    m_eventTypes->setTimeWindow( _data->eventTypesOccurrences() );

    m_filteredEventTypes->sort( 0 );

    setRunning( false );
}

void Filters::filterByEventType( qint32 _id, bool _value )
{
    if ( m_eventTypes.isNull() )
    {
        qCritical().nospace().noquote() << "ERROR: Event's types list is empty";
        return;
    }

    m_eventTypes->setEventVisibility( _id, _value );
}

void Filters::filterByEventTypeSelectAll()
{
    if ( m_eventTypes.isNull() )
    {
        qCritical().nospace().noquote() << "ERROR: Event's types list is empty";
        return;
    }

    m_eventTypes->selectAll();
}

void Filters::filterByEventTypeDeselectAll()
{
    if ( m_eventTypes.isNull() )
    {
        qCritical().nospace().noquote() << "ERROR: Event's types list is empty";
        return;
    }

    m_eventTypes->deselectAll();
}

void Filters::filterEventTypeNames( const QString& _value )
{
    if ( m_filteredEventTypes.isNull() )
    {
        qCritical().nospace().noquote() << "ERROR: Filtered event's types list is empty";
        return;
    }

    m_filteredEventTypes->filterNames( _value );
}
