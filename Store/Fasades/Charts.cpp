#include "Charts.h"

#include <algorithm>
#include <QDebug>

Charts::Charts()
{
    const int numberOfSamples = 100;

    for ( QList< double >::size_type i = 0; i < numberOfSamples; ++i )
    {
        m_eventsTimeline.push_back( 1.0 );
        m_filteredEventsTimeline.push_back( 1.0 );
    }
}

QList< double > Charts::eventsTimeline() const
{
    return m_eventsTimeline;
}

void Charts::setEventsTimeline( QSharedPointer< ProcessedData > _data )
{
    if ( _data.isNull() )
    {
        qCritical().nospace().noquote() << "ERROR: Processed data is empty";
        return;
    }

    m_eventsTimeline.clear();

    m_eventsTimeline = _data->histogram().toList();

    emit eventsTimelineChanged();
}

QList< double > Charts::filteredEventsTimeline() const
{
    return m_filteredEventsTimeline;
}

void Charts::setFilteredEventsTimeline( QSharedPointer< ProcessedData > _data )
{
    if ( _data.isNull() )
    {
        qCritical().nospace().noquote() << "ERROR: Processed data is empty";
        return;
    }

    m_filteredEventsTimeline.clear();

    m_filteredEventsTimeline = _data->filteredHistogram().toList();

    emit filteredEventsTimelineChanged();
}
