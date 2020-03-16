#include "ProcessedData.h"

#include <algorithm>

#ifdef PERF_LOGS
    #include "Utility/PerformanceLogger.h"
#endif

ProcessedData::ProcessedData() :
    m_data { },
    m_eventTypesOccurrences { },
    m_histogram { },
    m_maximalEventType { 1 },
    m_minimalEpoch { 0 },
    m_maximalEpoch { 0 },
    m_currentMinimalEpoch { 0 },
    m_currentMaximalEpoch { 0 },
    m_minimalEpochIndex { 0 },
    m_maximalEpochIndex { 0 }
{}

ProcessedData::~ProcessedData()
{
    clear();
}

void ProcessedData::process( const QVector< Event* >& _events )
{
    clear();

    m_data = _events;

    if ( m_data.isEmpty() )
        return;

    findMaximalEventType();

    m_minimalEpoch = m_data.first()->epoch();
    m_currentMinimalEpoch = m_data.first()->epoch();
    m_maximalEpoch = m_data.last()->epoch();
    m_currentMaximalEpoch = m_data.last()->epoch();

    findMinimumEpochIndex();
    findMaximumEpochIndex();

    findEventTypeOccurencesInRange();

    findHistogram();
}

void ProcessedData::setTimeWindow( qint64 _minimum, qint64 _maximum )
{
    m_currentMinimalEpoch = _minimum;
    m_currentMaximalEpoch = _maximum;

    findMinimumEpochIndex();
    findMaximumEpochIndex();

    findEventTypeOccurencesInRange();
}

const QVector< Event* >& ProcessedData::events() const
{
    return m_data;
}

qint32 ProcessedData::maximalEventType() const
{
    return m_maximalEventType;
}

const QVector< qint32 >& ProcessedData::eventTypesOccurrences() const
{
    return m_eventTypesOccurrences;
}

const QVector< double >& ProcessedData::histogram() const
{
    return m_histogram;
}

qint64 ProcessedData::currentMinimum() const
{
    return m_currentMinimalEpoch;
}

qint64 ProcessedData::currentMaximum() const
{
    return m_currentMaximalEpoch;
}

qint64 ProcessedData::minimumEpoch() const
{
    return m_minimalEpoch;
}

qint64 ProcessedData::maximumEpoch() const
{
    return m_maximalEpoch;
}

qint64 ProcessedData::minimumEpochIndex() const
{
    return m_minimalEpochIndex;
}

qint64 ProcessedData::maximumEpochIndex() const
{
    return m_maximalEpochIndex;
}

void ProcessedData::clear()
{
    if ( !m_data.isEmpty() )
    {
        qDeleteAll( m_data );
        m_data.clear();
    }

    m_eventTypesOccurrences.clear();
    m_histogram.clear();

    m_maximalEventType = 1;
    m_minimalEpoch = 0;
    m_maximalEpoch = 0;
    m_currentMinimalEpoch = 0;
    m_currentMaximalEpoch = 0;
}

void ProcessedData::findMaximalEventType()
{
    auto element = *std::max_element( m_data.begin(), m_data.end(), []( Event* _leftEvent, Event* _rightEvent )
    {
        return _leftEvent->type() < _rightEvent->type();
    });

    m_maximalEventType = element->type();
}

void ProcessedData::findEventTypeOccurencesInRange()
{
    BENCHMARK( "ProcessedData::findEventTypeOccurencesInRange()" )

    if ( m_data.isEmpty() )
    {
        qCritical().nospace().noquote() << "ERROR: Cannot compute types occurrences of empty data";
        return;
    }

    m_eventTypesOccurrences.clear();
    m_eventTypesOccurrences.fill( 0, m_maximalEventType + 1 );

    qint64 begin = m_minimalEpochIndex;
    qint64 end = m_maximalEpochIndex;

    for ( ; begin <= end; ++begin )
    {
        ++m_eventTypesOccurrences[ m_data[ begin ]->type() ];
    }
}

void ProcessedData::findHistogram()
{
    BENCHMARK( "ProcessedData::findHistogram()" )

    const qint32 numberOfSegments = 100;

    m_histogram.clear();
    m_histogram.fill( 0, numberOfSegments );

    QVector< double >::size_type i = 0;

    double delta = ( m_maximalEpoch - m_minimalEpoch ) / static_cast< double >( numberOfSegments );

    for ( const auto& event : m_data )
    {
        while ( i < numberOfSegments )
        {
            if ( event->epoch() >= ( ( i + 1 ) * delta + m_minimalEpoch ) )
                ++i;
            else
                break;
        }

        if ( i >= numberOfSegments)
        {
            Q_ASSERT( event->epoch() >= ( ( i - 1 ) * delta + m_minimalEpoch ) );
            Q_ASSERT( event->epoch() <= m_maximalEpoch );

            ++m_histogram[ numberOfSegments - 1 ];
        }
        else
        {
            Q_ASSERT( event->epoch() >= ( i * delta + m_minimalEpoch ) );
            Q_ASSERT( event->epoch() < ( ( i + 1 ) * delta + m_minimalEpoch ) );

            ++m_histogram[ i ];
        }
    }

    auto maxElement = *std::max_element( m_histogram.begin(), m_histogram.end() );

    for( auto& segment : m_histogram )
        segment = 1.0 - ( segment / maxElement );
}

void ProcessedData::findMinimumEpochIndex()
{
    int step = 0;
    int count = m_data.size();

    QVector< Event* >::iterator it;
    QVector< Event* >::iterator first = m_data.begin();

    while ( count > 0 )
    {
        it = first;
        step = count / 2;

        std::advance( it, step );

        if ( ( *it )->epoch() < m_currentMinimalEpoch )
        {
            first = ++it;
            count -= step + 1;
        }
        else
            count = step;
    }

    m_minimalEpochIndex = std::distance( m_data.begin(), first );
}

void ProcessedData::findMaximumEpochIndex()
{
    int step = 0;
    int count = m_data.size();

    QVector< Event* >::iterator it;
    QVector< Event* >::iterator first = m_data.begin();

    while ( count > 0 )
    {
        it = first;
        step = count / 2;

        std::advance( it, step );

        if ( !( m_currentMaximalEpoch < ( *it )->epoch() ) )
        {
            first = ++it;
            count -= step + 1;
        }
        else
            count = step;
    }

    if ( first == m_data.end() )
        m_maximalEpochIndex = m_data.size() - 1;
    else
        m_maximalEpochIndex = std::distance( m_data.begin(), first ) - 1;
}
