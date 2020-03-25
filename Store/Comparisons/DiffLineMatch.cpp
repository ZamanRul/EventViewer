#include "DiffLineMatch.h"

DiffLineMatch::DiffLineMatch( qint32 _lineA, qint32 _lineB ) :
    m_lineA { _lineA },
    m_lineB { _lineB },
    m_previous { nullptr }
{}

qint32 DiffLineMatch::indexA() const
{
    return m_lineA;
}

qint32 DiffLineMatch::indexB() const
{
    return m_lineB;
}

QSharedPointer< DiffLineMatch > DiffLineMatch::previous() const
{
    return m_previous;
}

void DiffLineMatch::setPrevious( QSharedPointer< DiffLineMatch > _previous )
{
    m_previous = _previous;
}
