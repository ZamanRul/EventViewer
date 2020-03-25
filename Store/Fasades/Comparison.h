#ifndef COMPARISION_H
#define COMPARISION_H

#include "../Comparisons/CompareEventsModel.h"

#include "../Event.h"
#include "../Comparisons/DiffLine.h"

#include <QObject>
#include <QSharedPointer>

class Comparison: public QObject
{
    Q_OBJECT

    Q_PROPERTY(QObject* compareEventsModel READ compareEventsModel NOTIFY compareEventsModelChanged)

public:

    Comparison();

    QObject* compareEventsModel() const;

    void compare( QVector< QSharedPointer< Event > >& _leftGroup, QVector< QSharedPointer< Event > >& _rightGroup );

signals:

    void compareEventsModelChanged();

private:

    QVector< QPair< QString, qint32 > > prepareGroupToCompare( const QVector< QSharedPointer< Event > >& _group );
    QVector< QSharedPointer< CompareEventsRow > > createCompareRows( const QVector< DiffLine >& _lines,
                                                                     const QVector< QSharedPointer< Event > >& _leftGroup,
                                                                     const QVector< QSharedPointer< Event > >& _rightGroup );

private:

    QSharedPointer< CompareEventsModel > m_compareEventsModel;
};

#endif // COMPARISION_H
