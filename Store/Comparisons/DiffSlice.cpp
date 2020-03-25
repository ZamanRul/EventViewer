#include "DiffSlice.h"

DiffSlice::DiffSlice( qint32 _a_low, qint32 _a_high, qint32 _b_low, qint32 _b_high) :
    m_a_low { _a_low },
    m_a_high { _a_high },
    m_b_low { _b_low },
    m_b_high { _b_high }
{}

qint32 DiffSlice::a_low() const
{
    return m_a_low;
}

qint32 DiffSlice::a_high() const
{
    return m_a_high;
}

qint32 DiffSlice::b_low() const
{
    return m_b_low;
}

qint32 DiffSlice::b_high() const
{
    return m_b_high;
}

bool DiffSlice::isEmpty() const
{
    return m_a_low >= m_a_high && m_b_low >= m_b_high;
}
