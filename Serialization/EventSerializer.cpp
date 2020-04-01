#include "EventSerializer.h"

#include <QStringBuilder>
#include <QDateTime>

#include <QDebug>

namespace
{
    const QString EVENT_LOG_FILE_NAME = QStringLiteral( "EventLog_" );
    const QString EVENT_LOG_FILE_EXTENSION = QStringLiteral( ".dat" );
    const QString DATE_FORMAT = QStringLiteral( "dd_MM_yy_hh_mm_ss" );

    const quint32 MAGIC_STAMP = static_cast< quint32 >( 0xA0B0C0D1 );
    const quint32 EVENT_LOG_VERSION = 1;
}

void EventSerializer::initialize()
{
    QString fileName = EVENT_LOG_FILE_NAME % QDateTime::currentDateTime().toString( DATE_FORMAT ) % EVENT_LOG_FILE_EXTENSION;

    m_file.setFileName( fileName );

    if ( !m_file.open( QIODevice::WriteOnly ) )
    {
        qCritical() << "Cannot open event log file '" << fileName << "'";

        return;
    }

    m_stream.setDevice( &m_file );

    m_stream << MAGIC_STAMP;
    m_stream << EVENT_LOG_VERSION;

    m_stream.setVersion( QDataStream::Qt_5_12 );
}

void EventSerializer::serialize( QObject* _receiver, QEvent* _event )
{
    if ( !_receiver || !_event )
    {
        return;
    }

    QString receiver = _receiver->metaObject()->className()
            % QStringLiteral( " (" )
            % QString( "0x%1" ).arg( reinterpret_cast< quintptr >( _receiver ), QT_POINTER_SIZE * 2, 16, QChar( '0' ) )
            % QStringLiteral( ", \"" )
            % _receiver->objectName()
            % QStringLiteral( "\")" );

    m_stream << QDateTime::currentMSecsSinceEpoch() << _event->type() << receiver;

    qDebug() << QDateTime::currentMSecsSinceEpoch() << _event->type() << receiver;

    switch ( _event->type() )
    {
        case QEvent::MouseButtonPress:
        case QEvent::MouseButtonRelease:
        case QEvent::MouseButtonDblClick:
        case QEvent::MouseMove:
            serializeMouseEvents( static_cast< QMouseEvent* >( _event ) );
            break;

        case QEvent::Timer:
            serializeTimerEvents( static_cast< QTimerEvent* >( _event ) );
            break;

        case QEvent::Paint:
            serializePaintEvents( static_cast< QPaintEvent* >( _event ) );
            break;

        case QEvent::FocusIn:
        case QEvent::FocusOut:
            serializeFocusEvents( static_cast< QFocusEvent* >( _event ) );
            break;

        case QEvent::GraphicsSceneWheel:
            serializeGraphicsSceneWheelEvents( static_cast< QGraphicsSceneWheelEvent* >( _event ) );
            break;

        case QEvent::GraphicsSceneMouseMove:
        case QEvent::GraphicsSceneMousePress:
        case QEvent::GraphicsSceneMouseRelease:
        case QEvent::GraphicsSceneMouseDoubleClick:
            serializeGraphicsSceneMouseEvents( static_cast< QGraphicsSceneMouseEvent* >( _event ) );
            break;

        case QEvent::KeyPress:
        case QEvent::KeyRelease:
            serializeKeyEvents( static_cast< QKeyEvent* >( _event ) );
            break;

        default:
            break;
    }
}

void EventSerializer::serializeMouseEvents( QMouseEvent* _event )
{
    m_stream << _event->pos() << _event->button();

    qDebug() << _event->pos() << _event->button();
}

void EventSerializer::serializeTimerEvents( QTimerEvent* _event )
{
    m_stream << _event->timerId();

    qDebug() << _event->timerId();
}

void EventSerializer::serializePaintEvents( QPaintEvent* _event )
{
    m_stream << _event->rect();

    qDebug() << _event->rect();
}

void EventSerializer::serializeFocusEvents( QFocusEvent* _event )
{
    m_stream << _event->gotFocus() << _event->lostFocus() << _event->reason();

    qDebug() << _event->gotFocus() << _event->lostFocus() << _event->reason();
}

void EventSerializer::serializeGraphicsSceneWheelEvents( QGraphicsSceneWheelEvent* _event )
{
    m_stream << _event->delta() << _event->modifiers();

    qDebug() << _event->delta() << _event->modifiers();
}

void EventSerializer::serializeGraphicsSceneMouseEvents( QGraphicsSceneMouseEvent* _event )
{
    m_stream << _event->pos() << _event->button() << _event->modifiers();

    qDebug() << _event->pos() << _event->button() << _event->modifiers();
}

void EventSerializer::serializeKeyEvents( QKeyEvent* _event )
{
    m_stream << _event->key() << _event->modifiers();

    qDebug() << _event->key() << _event->modifiers();
}
