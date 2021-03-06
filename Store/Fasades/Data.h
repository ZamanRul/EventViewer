#ifndef DATA_H
#define DATA_H

#include "../EventsList.h"
#include "../ProcessedData.h"

#include <QObject>
#include <QSharedPointer>

class Data: public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool noData READ noData NOTIFY noDataChanged)    
    Q_PROPERTY(QObject* eventsList READ eventsList NOTIFY eventsListChanged)
    Q_PROPERTY(qint32 groupACount READ groupACount NOTIFY groupACountChanged)
    Q_PROPERTY(qint32 groupBCount READ groupBCount NOTIFY groupBCountChanged)

public:

    Data();

    bool noData() const;
    void setNoData( bool _value );

    QObject* eventsList() const;

    qint32 affectedEvents() const;

    QSharedPointer< ProcessedData > processedData();

    qint32 groupACount() const;
    qint32 groupBCount() const;

    QVector< QSharedPointer< Event > > group( char _group );
    void setGroup( qint32 _id, char _value );
    void clearGroup( char _value );

    void registerData( const QVector< QSharedPointer< Event > >& _events );
    void setTimeWindow( qint64 _minimum, qint64 _maximum );
    void setEventVisibility( qint32 _id, bool _value );
    void selectAll();
    void deselectAll();

signals:

    void noDataChanged();
    void eventsListChanged();
    void groupACountChanged();
    void groupBCountChanged();

private:

    bool m_noData;

    QSharedPointer< EventsList > m_eventsList;
    QSharedPointer< ProcessedData > m_processedData;

    qint32 m_groupACount;
    qint32 m_groupBCount;
};

#endif // DATA_H
