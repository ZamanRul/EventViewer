#ifndef COMPAREEVENTSROW_H
#define COMPAREEVENTSROW_H

#include "ComparisonGlobals.h"

#include <QString>

class CompareEventsRow
{

public:

    CompareEventsRow( COMPARISION_RESULT _mode,
                      const QString& _typeString,
                      const QString& _dateTimeStringLeft,
                      const QString& _targetLeft,
                      const QString& _descriptionLeft,
                      const QString& _dateTimeStringRight,
                      const QString& _targetRight,
                      const QString& _descriptionRight );

    COMPARISION_RESULT rowMode() const;

    QString type() const;

    QString dateLeft() const;
    QString targetLeft() const;
    QString descriptionLeft() const;

    QString dateRight() const;
    QString targetRight() const;
    QString descriptionRight() const;

private:

    COMPARISION_RESULT m_rowMode;

    QString m_typeString;

    QString m_dateTimeStringLeft;
    QString m_targetLeft;
    QString m_descriptionLeft;

    QString m_dateTimeStringRight;
    QString m_targetRight;
    QString m_descriptionRight;
};

#endif // COMPAREEVENTSROW_H
