#ifndef EVENT_H
#define EVENT_H

#include <QtGlobal>
#include <QString>
#include <QMetaType>

class Event
{
public:

    Event(  qint64 _epoch,
            qint32 _type,
            const QString& _target,
            const QString& _description,
            const QString& _dateTimeString,
            const QString& _typeString );

    qint64 epoch() const;
    QString dateTime() const;

    qint32 type() const;
    QString typeName() const;

    QString target() const;
    QString description() const;

private:

    qint64 m_epoch;
    QString m_dateTimeString;

    qint32 m_type;
    QString m_typeString;

    QString m_target;
    QString m_description;
};

Q_DECLARE_METATYPE( Event* )

#endif // EVENT_H
