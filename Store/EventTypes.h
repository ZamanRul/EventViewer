#ifndef EVENTTYPES_H
#define EVENTTYPES_H

#include <QAbstractListModel>

class EventType
{
public:

    EventType( qint32 _id, const QString& _name, qint32 _occurance, bool _visible );

    qint32 id() const;
    QString name() const;
    qint32 occurance() const;
    bool visible() const;

    void setOccurence( qint32 _occurence );
    void setVisibility( bool _visible );

private:

    qint32 m_id;
    QString m_name;
    qint32 m_occurence;
    bool m_visible;
};

class EventTypes : public QAbstractListModel
{
    Q_OBJECT

public:

    ~EventTypes() override;

    void registerData( const QVector< qint32 > _occurrences );

    void setTimeWindow( const QVector< qint32 > _occurrences );
    void setEventVisibility( qint32 _id, bool _value );

    void selectAll();
    void deselectAll();

    int rowCount( const QModelIndex& _parent = QModelIndex() ) const override;
    QVariant data( const QModelIndex& _index, int _role = Qt::DisplayRole ) const override;

protected:

    void clean();

    QHash< int, QByteArray > roleNames() const override;

    EventType* createEventType( qint32 _id, qint32 _occurrence );

private:

    QVector< EventType* > m_eventTypes;

};

#endif // EVENTTYPES_H
