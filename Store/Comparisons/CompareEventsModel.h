#ifndef COMPAREEVENTSMODEL_H
#define COMPAREEVENTSMODEL_H

#include "CompareEventsRow.h"

#include <QAbstractListModel>
#include <QSharedPointer>

class CompareEventsModel : public QAbstractListModel
{
    Q_OBJECT

public:

    ~CompareEventsModel() override;

    void registerData( const QVector< QSharedPointer< CompareEventsRow > >& _data );

    int rowCount( const QModelIndex& _parent = QModelIndex() ) const override;
    QVariant data( const QModelIndex& _index, int _role = Qt::DisplayRole ) const override;

protected:

    QHash< int, QByteArray > roleNames() const override;

private:

    QVector< QSharedPointer< CompareEventsRow > > m_eventsRows;

};

#endif // COMPAREEVENTSMODEL_H
