#ifndef DIFFLINE_H
#define DIFFLINE_H

#include "ComparisonGlobals.h"

#include <QtGlobal>

class DiffLine
{
public:

    DiffLine() = default;

    DiffLine( COMPARISION_RESULT _result, qint32 _indexA, qint32 _indexB);

    COMPARISION_RESULT result() const;

    qint32 indexA() const;
    qint32 indexB() const;

private:

    COMPARISION_RESULT m_result;

    qint32 m_indexA;
    qint32 m_indexB;
};

#endif // DIFFLINE_H
