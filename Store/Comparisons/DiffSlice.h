#ifndef DIFFSLICE_H
#define DIFFSLICE_H

#include <QtGlobal>

class DiffSlice
{
public:

    DiffSlice(    qint32 _a_low, qint32 _a_high, qint32 _b_low, qint32 _b_high);


    qint32 a_low() const;
    qint32 a_high() const;
    qint32 b_low() const;
    qint32 b_high() const;

    bool isEmpty() const;

private:

    qint32 m_a_low;
    qint32 m_a_high;
    qint32 m_b_low;
    qint32 m_b_high;
};

#endif // DIFFSLICE_H
