#include "CompareEventsRow.h"

CompareEventsRow::CompareEventsRow( COMPARISION_RESULT _mode,
                  const QString& _typeString,
                  const QString& _dateTimeStringLeft,
                  const QString& _targetLeft,
                  const QString& _descriptionLeft,
                  const QString& _dateTimeStringRight,
                  const QString& _targetRight,
                  const QString& _descriptionRight ) :
    m_rowMode { _mode },
    m_typeString { _typeString },
    m_dateTimeStringLeft { _dateTimeStringLeft },
    m_targetLeft { _targetLeft },
    m_descriptionLeft { _descriptionLeft },
    m_dateTimeStringRight { _dateTimeStringRight },
    m_targetRight { _targetRight },
    m_descriptionRight { _descriptionRight }
{}

COMPARISION_RESULT CompareEventsRow::rowMode() const
{
    return m_rowMode;
}

QString CompareEventsRow::type() const
{
    return m_typeString;
}

QString CompareEventsRow::dateLeft() const
{
    return m_dateTimeStringLeft;
}

QString CompareEventsRow::targetLeft() const
{
    return m_targetLeft;
}

QString CompareEventsRow::descriptionLeft() const
{
    return m_descriptionLeft;
}

QString CompareEventsRow::dateRight() const
{
    return m_dateTimeStringRight;
}

QString CompareEventsRow::targetRight() const
{
    return m_targetRight;
}

QString CompareEventsRow::descriptionRight() const
{
    return m_descriptionRight;
}
