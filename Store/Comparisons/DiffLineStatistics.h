#ifndef DIFFLINESTATISTICS_H
#define DIFFLINESTATISTICS_H

#include <QtGlobal>

class DiffLineStatistics
{
public:

    DiffLineStatistics();

    qint32 indexA() const;
    qint32 countA() const;
    qint32 indexB() const;
    qint32 countB() const;

    void registerForA( qint32 _line );
    void registerForB( qint32 _line );

private:

    qint32 m_a_index;
    qint32 m_a_count;
    qint32 m_b_index;
    qint32 m_b_count;
};

#endif // DIFFLINESTATISTICS_H
