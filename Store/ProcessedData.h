#ifndef PROCESSEDDATA_H
#define PROCESSEDDATA_H

#include "Event.h"

#include <QVector>

class ProcessedData
{

public:

    ProcessedData();

    ~ProcessedData();

    void process( const QVector< Event* >& _events );

    void setTimeWindow( qint64 _minimum, qint64 _maximum );

    const QVector< Event* >& events() const;
    const QVector< qint32 >& eventTypesOccurrences() const;
    const QVector< double >& histogram() const;

    qint32 maximalEventType() const;

    qint64 currentMinimum() const;
    qint64 currentMaximum() const;
    qint64 minimumEpoch() const;
    qint64 maximumEpoch() const;

    qint64 minimumEpochIndex() const;
    qint64 maximumEpochIndex() const;

private:

    void clear();

    void findMaximalEventType();

    void findEventTypeOccurencesInRange();

    void findHistogram();

    void findMinimumEpochIndex();

    void findMaximumEpochIndex();

private:

    QVector< Event* > m_data;
    QVector< qint32 > m_eventTypesOccurrences;
    QVector< double > m_histogram;

    qint32 m_maximalEventType;

    qint64 m_minimalEpoch;
    qint64 m_maximalEpoch;

    qint64 m_currentMinimalEpoch;
    qint64 m_currentMaximalEpoch;

    qint64 m_minimalEpochIndex;
    qint64 m_maximalEpochIndex;
};

#endif // PROCESSEDDATA_H
