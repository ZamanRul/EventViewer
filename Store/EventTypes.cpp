#include "EventTypes.h"

#include "Roles.h"

#include <QEvent>
#include <QMetaEnum>

#include <QDebug>

#ifdef PERF_LOGS
    #include "Utility/PerformanceLogger.h"
#endif

EventType::EventType(qint32 _id, const QString& _name, qint32 _occurance, bool _visible ) :
    m_id { _id },
    m_name { _name },
    m_occurence { _occurance },
    m_visible { _visible }
{}

qint32 EventType::id() const
{
    return m_id;
}

QString EventType::name() const
{
    return m_name;
}

qint32 EventType::occurance() const
{
    return m_occurence;
}

bool EventType::visible() const
{
    return m_visible;
}

void EventType::setOccurence( qint32 _occurence )
{
    m_occurence = _occurence;
}

void EventType::setVisibility( bool _visible )
{
    m_visible = _visible;
}

EventTypes::~EventTypes()
{
    clean();
}

void EventTypes::registerData( const QVector< qint32 > _occurrences )
{
    BENCHMARK( "EventTypes::registerData()" )

    clean();

    if ( _occurrences.empty() )
    {
        qCritical().nospace().noquote() << "ERROR: Trying to register new data with empty occurrence's list";
        return;
    }

    beginInsertRows( index( 0, 0 ), 0, _occurrences.size() - 1 );

    m_eventTypes.fill( nullptr, _occurrences.size() );

    QString typeName;

    for ( QVector< qint32 >::size_type i = 1; i < _occurrences.size(); ++i )
    {
        if ( _occurrences[ i ] > 0 )
        {
            m_eventTypes[ i ] = createEventType( i, _occurrences[ i ] );
        }
    }

    endInsertRows();
}

void EventTypes::setTimeWindow( const QVector< qint32 > _occurrences )
{
    BENCHMARK( "EventTypes::setTimeWindow()" )

    if ( _occurrences.size() <= 1 )
    {
        qCritical().nospace().noquote() << "ERROR: Trying to set new time window with invalid occurrence's list";
        return;
    }

    for ( QVector< qint32 >::size_type i = 1; i < _occurrences.size(); ++i )
    {
        if ( m_eventTypes[ i ] )
            m_eventTypes[ i ]->setOccurence( _occurrences[ i ] );
    }

    QModelIndex bottom = createIndex( 0, 0 );
    QModelIndex top = createIndex( _occurrences.size() - 1, 0 );

    emit dataChanged( bottom, top, { EventTypesRoles::OccurenceRole } );
}

void EventTypes::setEventVisibility( qint32 _id, bool _value )
{
    if ( _id < 0 || _id >= m_eventTypes.size() || m_eventTypes[ _id ] == nullptr )
        return;

    m_eventTypes[ _id ]->setVisibility( _value );

    QModelIndex index = createIndex( _id, 0 );
    emit dataChanged( index, index );
}

void EventTypes::selectAll()
{
    beginResetModel();

    for ( auto& eventType : m_eventTypes )
    {
        if ( eventType != nullptr )
            eventType->setVisibility( true );
    }

    endResetModel();
}

void EventTypes::deselectAll()
{
    beginResetModel();

    for ( auto& eventType : m_eventTypes )
    {
        if ( eventType != nullptr )
            eventType->setVisibility( false );
    }

    endResetModel();
}

int EventTypes::rowCount( const QModelIndex& _parent ) const
{
    Q_UNUSED( _parent )
    return m_eventTypes.size();
}

QVariant EventTypes::data( const QModelIndex& _index, int _role ) const
{
    if ( _index.row() < 0 || _index.row() >= m_eventTypes.size() )
        return QVariant { };

    if ( _role == EventTypesRoles::NullRole )
        return m_eventTypes[ _index.row() ] == nullptr;

    if ( m_eventTypes[ _index.row() ] == nullptr )
        return QVariant { };

    if ( _role == EventTypesRoles::IdRole )
        return m_eventTypes[ _index.row() ]->id();
    else if( _role == EventTypesRoles::NameRole )
        return m_eventTypes[ _index.row() ]->name();
    else if( _role == EventTypesRoles::OccurenceRole )
        return m_eventTypes[ _index.row() ]->occurance();
    else if( _role == EventTypesRoles::VisibleRole )
        return m_eventTypes[ _index.row() ]->visible();
    else
        return QVariant { };
}

void EventTypes::clean()
{
    if ( !m_eventTypes.empty() )
    {
        beginResetModel();

        qDeleteAll( m_eventTypes );
        m_eventTypes.clear();

        endResetModel();
    }
}

QHash< int, QByteArray > EventTypes::roleNames() const
{
    QHash< int, QByteArray > roles;

    roles[ EventTypesRoles::NullRole ] = "empty";
    roles[ EventTypesRoles::IdRole ] = "id";
    roles[ EventTypesRoles::NameRole ] = "name";
    roles[ EventTypesRoles::OccurenceRole ] = "occurence";
    roles[ EventTypesRoles::VisibleRole ] = "show";

    return roles;
}

EventType* EventTypes::createEventType( qint32 _id, qint32 _occurrence )
{
    static int eventEnumIndex = QEvent::staticMetaObject.indexOfEnumerator( "Type" );

    QString typeName = QEvent::staticMetaObject.enumerator( eventEnumIndex ).valueToKey( _id );

    if ( typeName.isEmpty() )
        typeName = QString( "Undefined(%1)" ).arg( _id );

    return new EventType { _id, typeName, _occurrence, true };
}
