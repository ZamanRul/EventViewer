#include "DiffLineStatistics.h"

DiffLineStatistics::DiffLineStatistics() :
    m_a_index { -1 },
    m_a_count { 0 },
    m_b_index { -1 },
    m_b_count { 0 }
{}

qint32 DiffLineStatistics::indexA() const
{
    return m_a_index;
}

qint32 DiffLineStatistics::countA() const
{
    return m_a_count;
}

qint32 DiffLineStatistics::indexB() const
{
    return m_b_index;
}

qint32 DiffLineStatistics::countB() const
{
    return m_b_count;
}

void DiffLineStatistics::registerForA( qint32 _line )
{
    if ( m_a_index == -1 )
        m_a_index = _line;

    ++m_a_count;
}

void DiffLineStatistics::registerForB( qint32 _line )
{
    if ( m_b_index == -1 )
        m_b_index = _line;

    ++m_b_count;
}
