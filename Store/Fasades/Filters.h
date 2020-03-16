#ifndef FILTERS_H
#define FILTERS_H

#include "Store/EventTypes.h"
#include "Store/FilteredEventTypes.h"
#include "Store/Event.h"
#include "Store/ProcessedData.h"

#include <QObject>
#include <QSharedPointer>

class Filters : public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool running READ running NOTIFY runningChanged)
    Q_PROPERTY(QObject* filteredEventTypes READ filteredEventTypes NOTIFY filteredEventTypesChanged)

public:

    Filters();

    bool running() const;

    QObject* filteredEventTypes() const;

    void registerData( QSharedPointer< ProcessedData > _data );

    void filterByTime( QSharedPointer< ProcessedData > _data );
    void filterByEventType( qint32 _id, bool _value );

    void filterByEventTypeSelectAll();
    void filterByEventTypeDeselectAll();

    void filterEventTypeNames( const QString& _value );

signals:

    void runningChanged();
    void filteredEventTypesChanged();

private:

    void setRunning( bool _running );

private:

    bool m_running;

    QSharedPointer< EventTypes > m_eventTypes;
    QSharedPointer< FilteredEventTypes > m_filteredEventTypes;
};

#endif // FILTERS_H
