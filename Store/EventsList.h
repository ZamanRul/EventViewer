#ifndef EVENTSLIST_H
#define EVENTSLIST_H

#include "Event.h"
#include "ProcessedData.h"

#include <QAbstractListModel>

class EventsList : public QAbstractListModel
{
    Q_OBJECT

    Q_PROPERTY(qint64 currentMinimum READ currentMinimum NOTIFY currentMinimumChanged)
    Q_PROPERTY(qint64 currentMaximum READ currentMaximum NOTIFY currentMaximumChanged)
    Q_PROPERTY(qint64 minimumEpoch READ minimumEpoch NOTIFY minimumEpochChanged)
    Q_PROPERTY(qint64 maximumEpoch READ maximumEpoch NOTIFY maximumEpochChanged)

public:

    EventsList( QObject* _parent = nullptr );

    ~EventsList() override;

    void registerData( QSharedPointer< ProcessedData > _data );

    int rowCount( const QModelIndex& _parent = QModelIndex() ) const override;

    QVariant data( const QModelIndex& _index, int _role = Qt::DisplayRole ) const override;

    void setTimeWindow( QSharedPointer< ProcessedData > _data );
    void setEventVisibility( qint32 _id, bool _value );

    void selectAll();
    void deselectAll();

    const QVector< Event* >& events() const;

    qint64 currentMinimum() const;
    qint64 currentMaximum() const;
    qint64 minimumEpoch() const;
    qint64 maximumEpoch() const;

signals:

    void currentMinimumChanged();
    void currentMaximumChanged();
    void minimumEpochChanged();
    void maximumEpochChanged();

protected:

    void invalidateFilter();

    void setCurrentMinimum( qint64 _value );
    void setCurrentMaximum( qint64 _value );
    void setMinimumEpoch( qint64 _value );
    void setMaximumEpoch( qint64 _value );

    QHash< int, QByteArray > roleNames() const override;

private:

    QVector< Event* > m_events;
    QVector< Event* > m_filteredEvents;

    qint64 m_minimalDateEpoch;
    qint64 m_maximalDateEpoch;

    qint64 m_currentMinimalEpoch;
    qint64 m_currentMaximalEpoch;

    qint64 m_currentMinimalEpochIndex;
    qint64 m_currentMaximalEpochIndex;

    QVector< bool > m_eventsTypeMask;
};

#endif // EVENTSLIST_H
