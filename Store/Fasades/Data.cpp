#include "Data.h"

#include <QDebug>

Data::Data() :
    m_noData { true },
    m_eventsList { new EventsList { } },
    m_processedData { new ProcessedData { } }
{}

bool Data::noData() const
{
    return m_noData;
}

void Data::setNoData( bool _value )
{
    if ( m_noData != _value )
    {
        m_noData = _value;

        emit noDataChanged();
    }
}

QObject* Data::eventsList() const
{
    return m_eventsList.get();
}

qint32 Data::affectedEvents() const
{
    return m_eventsList->rowCount();
}

QSharedPointer< ProcessedData > Data::processedData()
{
    return m_processedData;
}

void Data::registerData( const QVector< Event* >& _events )
{
    if ( m_eventsList.isNull() )
    {
        qCritical().nospace().noquote() << "ERROR: Events list is empty";
        return;
    }

    if ( m_processedData.isNull() )
    {
        qCritical().nospace().noquote() << "ERROR: Processed data is empty";
        return;
    }

    setNoData( false );

    m_processedData->process( _events );

    m_eventsList->registerData( m_processedData );
}

void Data::setTimeWindow( qint64 _minimum, qint64 _maximum )
{
    if ( m_eventsList.isNull() )
    {
        qCritical().nospace().noquote() << "ERROR: Events list is empty";
        return;
    }

    if ( m_processedData.isNull() )
    {
        qCritical().nospace().noquote() << "ERROR: Processed data is empty";
        return;
    }

    m_processedData->setTimeWindow( _minimum, _maximum );

    m_eventsList->setTimeWindow( m_processedData );
}

void Data::setEventVisibility( qint32 _id, bool _value )
{
    m_eventsList->setEventVisibility( _id, _value );
}

void Data::selectAll()
{
    if ( m_eventsList.isNull() )
    {
        qCritical().nospace().noquote() << "ERROR: Events list is empty";
        return;
    }

    m_eventsList->selectAll();
}

void Data::deselectAll()
{
    if ( m_eventsList.isNull() )
    {
        qCritical().nospace().noquote() << "ERROR: Events list is empty";
        return;
    }

    m_eventsList->deselectAll();
}
