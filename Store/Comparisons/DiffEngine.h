#ifndef DIFFENGINE_H
#define DIFFENGINE_H

#include "DiffLine.h"
#include "DiffSlice.h"
#include "DiffLineMatch.h"

#include <QVector>
#include <QString>

class DiffEngine
{
public:

    DiffEngine( const QVector< QPair< QString, qint32 > >& _listA, const QVector< QPair< QString, qint32 > >& _listB );

    QVector< DiffLine > run();

private:

    QVector< DiffLine > diff( const DiffSlice& _slice );

    QVector< QSharedPointer< DiffLineMatch > > findUniqueLines( const DiffSlice& _slice );
    QVector< QSharedPointer< DiffLineMatch > > patienceSort( const QVector< QSharedPointer< DiffLineMatch > >& _matches );

    QVector< DiffLine > fallbackDiff( const DiffSlice& _slice );

private:

    QVector< QPair< QString, qint32 > > m_listA;
    QVector< QPair< QString, qint32 > > m_listB;

};

#endif // DIFFENGINE_H
