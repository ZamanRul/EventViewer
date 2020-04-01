#ifndef EVENTSERIALIZATION_H
#define EVENTSERIALIZATION_H

#include <QDataStream>
#include <QFile>

#include <QEvent>
#include <QTimerEvent>
#include <QMouseEvent>
#include <QGraphicsSceneWheelEvent>
#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>

/*
    Use this class in application you want to investigate.
    I propose to invoke method serialize() in overrided QCoreApplication::notify().

    REMEMBER! THIS FILE MUST BE CONSISTENT WITH LOG READER!
*/
class EventSerializer
{
public:

    void initialize();

    void serialize( QObject* _receiver, QEvent* _event );

private:

    void serializeMouseEvents( QMouseEvent* _event );
    void serializeTimerEvents( QTimerEvent* _event );
    void serializePaintEvents( QPaintEvent* _event );
    void serializeFocusEvents( QFocusEvent* _event );
    void serializeGraphicsSceneWheelEvents( QGraphicsSceneWheelEvent* _event );
    void serializeGraphicsSceneMouseEvents( QGraphicsSceneMouseEvent* _event );
    void serializeKeyEvents( QKeyEvent* _event );

private:

    QFile m_file;
    QDataStream m_stream;
};

#endif
