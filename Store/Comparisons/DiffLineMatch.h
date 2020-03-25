#ifndef DIFFLINEMATCH_H
#define DIFFLINEMATCH_H

#include <QSharedPointer>

class DiffLineMatch
{
public:

    DiffLineMatch( qint32 _lineA, qint32 _lineB );

    qint32 indexA() const;
    qint32 indexB() const;

    QSharedPointer< DiffLineMatch > previous() const;

    void setPrevious( QSharedPointer< DiffLineMatch > _previous );

private:

    qint32 m_lineA;
    qint32 m_lineB;

    QSharedPointer< DiffLineMatch > m_previous;
};

#endif // DIFFLINEMATCH_H
