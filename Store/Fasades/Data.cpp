#include "Data.h"

#include <QDebug>

Data::Data() :
    m_noData { true },
    m_eventsList { new EventsList { } },
    m_processedData { new ProcessedData { } },
    m_groupACount { 0 },
    m_groupBCount { 0 }
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

qint32 Data::groupACount() const
{
    return m_groupACount;
}

qint32 Data::groupBCount() const
{
    return m_groupBCount;
}

QVector< QSharedPointer< Event > > Data::group( char _group )
{
    if ( m_eventsList.isNull() )
    {
        qCritical().nospace().noquote() << "ERROR: Events list is empty";
        return QVector< QSharedPointer< Event > > { };
    }

    return m_eventsList->group( _group );
}

void Data::registerData( const QVector< QSharedPointer< Event > >& _events )
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

    clearGroup( 'A' );
    clearGroup( 'B' );

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

    m_eventsList->setEventVisibility( _id, _value );

    m_processedData->setEventVisibility( _id, _value );
}

void Data::selectAll()
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

    m_eventsList->selectAll();

    m_processedData->selectAll();
}

void Data::deselectAll()
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

    m_eventsList->deselectAll();

    m_processedData->deselectAll();
}

void Data::setGroup( qint32 _id, char _value )
{
    if ( m_eventsList.isNull() )
    {
        qCritical().nospace().noquote() << "ERROR: Events list is empty";
        return;
    }

    auto operation = m_eventsList->setGroup( _id, _value );

    if ( operation == EventsList::GROUP_OPERATION::INC_A || operation == EventsList::GROUP_OPERATION::INC_A_DEC_B )
    {
        ++m_groupACount;
    }
    if ( operation == EventsList::GROUP_OPERATION::INC_B || operation == EventsList::GROUP_OPERATION::INC_B_DEC_A )
    {
        ++m_groupBCount;
    }
    if ( operation == EventsList::GROUP_OPERATION::DEC_A || operation == EventsList::GROUP_OPERATION::INC_B_DEC_A )
    {
        --m_groupACount;
    }
    if ( operation == EventsList::GROUP_OPERATION::DEC_B || operation == EventsList::GROUP_OPERATION::INC_A_DEC_B )
    {
        --m_groupBCount;
    }

    emit groupACountChanged();
    emit groupBCountChanged();
}

void Data::clearGroup( char _value )
{
    if ( m_eventsList.isNull() )
    {
        qCritical().nospace().noquote() << "ERROR: Events list is empty";
        return;
    }

    m_eventsList->clearGroup( _value );

    if ( _value == 'A' )
    {
        m_groupACount = 0;
        emit groupACountChanged();
    }
    else if ( _value == 'B' )
    {
        m_groupBCount = 0;
        emit groupBCountChanged();
    }
}
