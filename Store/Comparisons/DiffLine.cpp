#include "DiffLine.h"

DiffLine::DiffLine( COMPARISION_RESULT _result, qint32 _indexA, qint32 _indexB) :
    m_result { _result },
    m_indexA { _indexA },
    m_indexB { _indexB }
{}

COMPARISION_RESULT DiffLine::result() const
{
    return m_result;
}

qint32 DiffLine::indexA() const
{
    return m_indexA;
}

qint32 DiffLine::indexB() const
{
    return m_indexB;
}
