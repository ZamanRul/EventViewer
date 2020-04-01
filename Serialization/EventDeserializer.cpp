#include "EventDeserializer.h"

#include "Store/EventFactory.h"

#include <QStringBuilder>
#include <QDateTime>

#include <QDebug>

namespace
{
    const quint32 MAGIC_STAMP = static_cast< quint32 >( 0xA0B0C0D1 );
    const quint32 EVENT_LOG_VERSION = 1;
}

namespace
{
    QString mouseButtonToString( Qt::MouseButton _button )
    {
        switch ( _button )
        {
            case Qt::NoButton:
                return QStringLiteral( "no" );

            case Qt::LeftButton:
                return QStringLiteral( "left" );

            case Qt::RightButton:
                return QStringLiteral( "right" );

            case Qt::MiddleButton:
                return QStringLiteral( "middle" );

            case Qt::AllButtons:
                return QStringLiteral( "all" );

            default:
                return QStringLiteral( "unknown" );
        }
    }

    QString focusReasonToString( Qt::FocusReason _reason )
    {
        switch ( _reason )
        {
            case Qt::MouseFocusReason:
                return QStringLiteral( "mouse interaction" );

            case Qt::TabFocusReason:
                return QStringLiteral( "tab interaction" );

            case Qt::BacktabFocusReason:
                return QStringLiteral( "backtab interaction" );

            case Qt::ActiveWindowFocusReason:
                return QStringLiteral( "window system" );

            case Qt::PopupFocusReason:
                return QStringLiteral( "opening the popup" );

            case Qt::ShortcutFocusReason:
                return QStringLiteral( "label shortcut" );

            case Qt::MenuBarFocusReason:
                return QStringLiteral( "opening the menu" );

            case Qt::OtherFocusReason:
                return QStringLiteral( "other reason" );

            case Qt::NoFocusReason:
                return QStringLiteral( "unknown interaction" );
        }
    }
}

DESERIALIZATION_RESULT EventDeserializer::deserialize( const QUrl& _path, QList< QVariant >& _events )
{
    m_file.setFileName( _path.toLocalFile() );

    if ( !m_file.open( QIODevice::ReadOnly ) )
    {
        return DESERIALIZATION_RESULT::CANNOT_OPEN_FILE;
    }

    m_stream.setDevice( &m_file );

    quint32 stamp = 0;
    m_stream >> stamp;

    if ( stamp != MAGIC_STAMP )
    {
        return DESERIALIZATION_RESULT::INCORRECT_STAMP;
    }

    quint32 version = 0;
    m_stream >> version;

    if ( version != EVENT_LOG_VERSION )
    {
        return DESERIALIZATION_RESULT::INCORRECT_VERSION;
    }

    m_stream.setVersion( QDataStream::Qt_5_12 );

    while ( !m_stream.atEnd() )
    {
        QSharedPointer< Event > event = deserializeEvent();

        _events.push_back( QVariant::fromValue( event ) );
    }

    return DESERIALIZATION_RESULT::SUCCESS;
}

QSharedPointer< Event > EventDeserializer::deserializeEvent()
{
    qint64 epoch = 0;
    QEvent::Type type = QEvent::None;
    QString target;
    QString description;

    m_stream >> epoch >> type >> target;

    switch ( type )
    {
        case QEvent::MouseButtonPress:
        case QEvent::MouseButtonRelease:
        case QEvent::MouseButtonDblClick:
        case QEvent::MouseMove:
            deserializeMouseEvents( type, description );
            break;

        case QEvent::Timer:
            deserializeTimerEvents( description );
            break;

        case QEvent::Paint:
            deserializePaintEvents( description );
            break;

        case QEvent::FocusIn:
        case QEvent::FocusOut:
            deserializeFocusEvents( description );
            break;

        case QEvent::GraphicsSceneWheel:
            deserializeGraphicsSceneWheelEvents( description );
            break;

        case QEvent::GraphicsSceneMouseMove:
        case QEvent::GraphicsSceneMousePress:
        case QEvent::GraphicsSceneMouseRelease:
        case QEvent::GraphicsSceneMouseDoubleClick:
            deserializeGraphicsSceneMouseEvents( type, description );
            break;

        case QEvent::KeyPress:
        case QEvent::KeyRelease:
            deserializeKeyEvents( type, description );
            break;

        default:
            break;
    }

    return EventFactory::instance().create( epoch, type, target, description );
}

void EventDeserializer::deserializeMouseEvents( QEvent::Type _type, QString& _description )
{
    QPoint position;
    Qt::MouseButton button;

    m_stream >> position >> button;

    switch ( _type )
    {
        case QEvent::MouseButtonPress:
            _description = QStringLiteral( "Pressing " )
                    % mouseButtonToString( button )
                    % QStringLiteral( " button at ")
                    % QString( QStringLiteral( "[%1, %2]" ) ).arg( position.x() ).arg( position.y() );
            break;

        case QEvent::MouseButtonRelease:
            _description = QStringLiteral( "Releasing " )
                    % mouseButtonToString( button )
                    % QStringLiteral( " button at ")
                    % QString( QStringLiteral( "[%1, %2]" ) ).arg( position.x() ).arg( position.y() );
            break;

        case QEvent::MouseButtonDblClick:
            _description = QStringLiteral( "Double clicking " )
                    % mouseButtonToString( button )
                    % QStringLiteral( " button at ")
                    % QString( QStringLiteral( "[%1, %2]" ) ).arg( position.x() ).arg( position.y() );
            break;

        case QEvent::MouseMove:
            _description = QStringLiteral( "Moving mouse to ")
                    % QString( QStringLiteral( "[%1, %2]" ) ).arg( position.x() ).arg( position.y() );
            break;

        default:

            break;
    }
}

void EventDeserializer::deserializeTimerEvents( QString& _description )
{
    int timerId = 0;

    m_stream >> timerId;

    _description = QStringLiteral( "Triggering timer (id: %1)").arg( timerId );
}

void EventDeserializer::deserializePaintEvents( QString& _description )
{
    QRect rect;
    m_stream >> rect;

   _description = QStringLiteral( "Painting region [x: %1, y: %2, width: %3, height: %4]")
           .arg( rect.x() )
           .arg( rect.y() )
           .arg( rect.width() )
           .arg( rect.height() );
}

void EventDeserializer::deserializeFocusEvents( QString& _description )
{
    bool getFocus = false;
    bool lostFocus = false;
    Qt::FocusReason reason;

    m_stream >> getFocus >> lostFocus >> reason;

    if ( getFocus )
    {
        _description = QStringLiteral( "Receiving focus because of ") % focusReasonToString( reason );
    }
    else if ( lostFocus )
    {
        _description = QStringLiteral( "Giving focus because of ") % focusReasonToString( reason );
    }
}

void EventDeserializer::deserializeGraphicsSceneWheelEvents( QString& _description )
{
    int delta = 0;
    Qt::KeyboardModifiers modifiers;

    m_stream >> delta >> modifiers;

    _description = QStringLiteral( "Rotating wheel by delta: %1").arg( delta );
}

void EventDeserializer::deserializeGraphicsSceneMouseEvents( QEvent::Type _type, QString& _description )
{
    QPointF position;
    Qt::MouseButton button;
    Qt::KeyboardModifiers modifiers;

    m_stream >> position >> button >> modifiers;

    switch ( _type )
    {
        case QEvent::GraphicsSceneMousePress:
            _description = QStringLiteral( "Pressing " )
                    % mouseButtonToString( button )
                    % QStringLiteral( " button at ")
                    % QString( QStringLiteral( "[%1, %2]" ) ).arg( position.x() ).arg( position.y() );
            break;

        case QEvent::GraphicsSceneMouseRelease:
            _description = QStringLiteral( "Releasing " )
                    % mouseButtonToString( button )
                    % QStringLiteral( " button at ")
                    % QString( QStringLiteral( "[%1, %2]" ) ).arg( position.x() ).arg( position.y() );
            break;

        case QEvent::GraphicsSceneMouseDoubleClick:
            _description = QStringLiteral( "Double clicking " )
                    % mouseButtonToString( button )
                    % QStringLiteral( " button at ")
                    % QString( QStringLiteral( "[%1, %2]" ) ).arg( position.x() ).arg( position.y() );
            break;

        case QEvent::GraphicsSceneMouseMove:
            _description = QStringLiteral( "Moving mouse to ")
                    % QString( QStringLiteral( "[%1, %2]" ) ).arg( position.x() ).arg( position.y() );
            break;

        default:

            break;
    }
}

void EventDeserializer::deserializeKeyEvents( QEvent::Type _type, QString& _description )
{
    int key = 0;
    Qt::KeyboardModifiers modifiers;

    m_stream >> key >> modifiers;

    QString text;

    if ( modifiers.testFlag( Qt::ShiftModifier ) )
        text += QStringLiteral( "SHIFT + " );
    if ( modifiers.testFlag( Qt::ControlModifier ) )
        text += QStringLiteral( "CTRL + " );
    if ( modifiers.testFlag( Qt::AltModifier ) )
        text += QStringLiteral( "ALT + " );
    if ( modifiers.testFlag( Qt::MetaModifier ) )
        text += QStringLiteral( "META + " );
    if ( modifiers.testFlag( Qt::KeypadModifier ) )
        text += QStringLiteral( "KEYPAD + " );

    text += QKeySequence( key ).toString();

    if ( _type == QEvent::KeyPress )
        _description = QStringLiteral( "Pressing key ") % text;
    else if ( _type == QEvent::KeyRelease )
        _description = QStringLiteral( "Releasing key ") % text;
}
