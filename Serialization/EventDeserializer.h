#ifndef EVENTDESERIALIZER_H
#define EVENTDESERIALIZER_H

#include "Store/Event.h"

#include <QDataStream>
#include <QFile>
#include <QSharedPointer>

#include <QEvent>
#include <QTimerEvent>
#include <QMouseEvent>
#include <QGraphicsSceneWheelEvent>
#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>

/*
    REMEMBER! THIS CLASS MUST BE CONSISTENT WITH EVENT SERIALIZER!
*/

enum class DESERIALIZATION_RESULT { SUCCESS, CANNOT_OPEN_FILE, INCORRECT_STAMP, INCORRECT_VERSION };

class EventDeserializer
{
public:

    DESERIALIZATION_RESULT deserialize( const QUrl& _path, QList< QVariant >& _events );

private:

    QSharedPointer< Event > deserializeEvent();

    void deserializeMouseEvents( QEvent::Type _type, QString& _description );
    void deserializeTimerEvents( QString& _description );
    void deserializePaintEvents( QString& _description );
    void deserializeFocusEvents( QString& _description );
    void deserializeGraphicsSceneWheelEvents( QString& _description );
    void deserializeGraphicsSceneMouseEvents( QEvent::Type _type, QString& _description );
    void deserializeKeyEvents( QEvent::Type _type, QString& _description );

private:

    QFile m_file;
    QDataStream m_stream;
};

#endif // EVENTDESERIALIZER_H
