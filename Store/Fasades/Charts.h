#ifndef CHARTS_H
#define CHARTS_H

#include "../ProcessedData.h"

#include <QObject>
#include <QSharedPointer>
#include <QList>

class Charts: public QObject
{
    Q_OBJECT

    Q_PROPERTY(QList<double> eventsTimeline READ eventsTimeline NOTIFY eventsTimelineChanged)
    Q_PROPERTY(QList<double> filteredEventsTimeline READ filteredEventsTimeline NOTIFY filteredEventsTimelineChanged)

public:

    Charts();

    QList< double > eventsTimeline() const;
    void setEventsTimeline( QSharedPointer< ProcessedData > _data );

    QList< double > filteredEventsTimeline() const;
    void setFilteredEventsTimeline( QSharedPointer< ProcessedData > _data );

signals:

    void eventsTimelineChanged();
    void filteredEventsTimelineChanged();

private:

    QList< double > m_eventsTimeline;
    QList< double > m_filteredEventsTimeline;
};

#endif // CHARTS_H
