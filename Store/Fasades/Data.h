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

public:

    Data();

    bool noData() const;
    void setNoData( bool _value );

    QObject* eventsList() const;

    qint32 affectedEvents() const;

    QSharedPointer< ProcessedData > processedData();

    void registerData( const QVector< Event* >& _events );
    void setTimeWindow( qint64 _minimum, qint64 _maximum );
    void setEventVisibility( qint32 _id, bool _value );
    void selectAll();
    void deselectAll();

signals:

    void noDataChanged();
    void eventsListChanged();

private:

    bool m_noData;

    QSharedPointer< EventsList > m_eventsList;
    QSharedPointer< ProcessedData > m_processedData;
};

#endif // DATA_H
