#include "Charts.h"

#include <algorithm>
#include <QDebug>

Charts::Charts()
{
    const int numberOfSamples = 100;

    for ( QList< double >::size_type i = 0; i < numberOfSamples; ++i )
    {
        m_eventsTimeline.push_back( 1.0 );
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
