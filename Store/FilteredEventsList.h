#ifndef FILTEREDEVENTLIST_H
#define FILTEREDEVENTLIST_H

#include "Event.h"
#include "EventsList.h"

#include <QSharedPointer>

class FilteredEventsList : public QObject
{
    Q_OBJECT

    Q_PROPERTY(qint64 currentMinimum READ currentMinimum NOTIFY currentMinimumChanged)
    Q_PROPERTY(qint64 currentMaximum READ currentMaximum NOTIFY currentMaximumChanged)
    Q_PROPERTY(qint64 minimumEpoch READ minimumEpoch NOTIFY minimumEpochChanged)
    Q_PROPERTY(qint64 maximumEpoch READ maximumEpoch NOTIFY maximumEpochChanged)

public:

    FilteredEventsList( QObject* _parent = nullptr );

    void setModel( QSharedPointer< EventsList > _model );

    void registerData( const QVector< Event* >& _events );

    void setTimeWindow( qint64 _minimalEpoch, qint64 _maximalEpoch );
    void setEventVisibility( qint32 _id, bool _value );

    void selectAll();
    void deselectAll();

    qint64 currentMinimum() const;
    qint64 currentMaximum() const;
    qint64 minimumEpoch() const;
    qint64 maximumEpoch() const;

protected:

    void invalidateFilter();

    void setCurrentMinimum( qint64 _value );
    void setCurrentMaximum( qint64 _value );
    void setMinimumEpoch( qint64 _value );
    void setMaximumEpoch( qint64 _value );

signals:

    void currentMinimumChanged();
    void currentMaximumChanged();
    void minimumEpochChanged();
    void maximumEpochChanged();

private:

    QSharedPointer< EventsList > m_eventsModel;

    qint64 m_minimalDateEpoch;
    qint64 m_maximalDateEpoch;

    qint64 m_currentMinimalEpoch;
    qint64 m_currentMaximalEpoch;

    QVector< bool > m_eventsTypeMask;

    QVector< Event* > m_events;
};

#endif // FILTEREDEVENTLIST_H
