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

public:

    Charts();

    QList< double > eventsTimeline() const;
    void setEventsTimeline( QSharedPointer< ProcessedData > _data );

signals:

    void eventsTimelineChanged();

private:

    QList< double > m_eventsTimeline;
};

#endif // CHARTS_H
