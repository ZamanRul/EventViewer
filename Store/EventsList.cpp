#include "EventsList.h"

#include "Roles.h"

#ifdef PERF_LOGS
    #include "Utility/PerformanceLogger.h"
#endif

EventsList::EventsList( QObject* _parent ) :
    QAbstractListModel { _parent },
    m_minimalDateEpoch { 0 },
    m_maximalDateEpoch { 0 },
    m_currentMinimalEpoch { 0 },
    m_currentMaximalEpoch { 0 },
    m_currentMinimalEpochIndex { 0 },
    m_currentMaximalEpochIndex { 0 },
    m_eventsTypeMask { }
{}

EventsList::~EventsList()
{
    if ( !m_events.empty() )
    {
        beginResetModel();

        m_events.clear();
        m_filteredEvents.clear();

        endResetModel();
    }
}

void EventsList::registerData( QSharedPointer< ProcessedData > _data )
{
    BENCHMARK( "EventsList::registerData()" )

    if ( _data.isNull() )
    {
        qCritical().nospace().noquote() << "ERROR: Cannot register empty data";
        return;
    }

    m_events.clear();

    m_events = _data->events();

    m_filteredEvents.reserve( m_events.size() );
    m_eventsTypeMask.fill( true, _data->maximalEventType() + 1 );

    setMinimumEpoch( _data->minimumEpoch() );
    setMaximumEpoch( _data->maximumEpoch() );
    setCurrentMinimum( _data->currentMinimum() );
    setCurrentMaximum( _data->currentMaximum() );

    m_currentMinimalEpochIndex = _data->minimumEpochIndex();
    m_currentMaximalEpochIndex = _data->maximumEpochIndex();

    invalidateFilter();
}

void EventsList::invalidateFilter()
{
    BENCHMARK( "EventsList::invalidateFilter()" )

    if ( m_events.isEmpty() )
        return;

    beginResetModel();

    m_filteredEvents.clear();

    QSharedPointer< Event > event = nullptr;

    for ( qint64 i = m_currentMinimalEpochIndex; i <= m_currentMaximalEpochIndex; ++i )
    {
        event = m_events[ i ];

        if ( m_eventsTypeMask[ event->type() ] == false )
            continue;

        m_filteredEvents << event;
    }

    endResetModel();
}

int EventsList::rowCount( const QModelIndex& _parent ) const
{
    Q_UNUSED(_parent)
    return m_filteredEvents.size();
}

QVariant EventsList::data( const QModelIndex& _index, int _role ) const
{
    if ( _index.row() < 0 || _index.row() >= m_filteredEvents.size() || m_filteredEvents[ _index.row() ] == nullptr )
        return QVariant { };

    if ( _role == EventsListRoles::TimeRole )
        return m_filteredEvents[ _index.row() ]->dateTime();
    else if ( _role == EventsListRoles::EpochRole )
        return m_filteredEvents[ _index.row() ]->epoch();
    else if ( _role == EventsListRoles::TypeRole )
        return m_filteredEvents[ _index.row() ]->typeName();
    else if ( _role == EventsListRoles::TypeIdRole )
        return m_filteredEvents[ _index.row() ]->type();
    else if ( _role == EventsListRoles::TargetRole )
        return m_filteredEvents[ _index.row() ]->target();
    else if ( _role == EventsListRoles::DescriptionRole )
        return m_filteredEvents[ _index.row() ]->description();
    else if ( _role == EventsListRoles::GroupRole )
        return m_filteredEvents[ _index.row() ]->group();
    else
        return QVariant { };
}

const QVector< QSharedPointer< Event > >& EventsList::events() const
{
    return m_events;
}

QHash< int, QByteArray > EventsList::roleNames() const
{
    QHash< int, QByteArray > roles;

    roles[ EventsListRoles::TimeRole ] = "time";
    roles[ EventsListRoles::EpochRole ] = "epoch";
    roles[ EventsListRoles::TypeIdRole ] = "typeId";
    roles[ EventsListRoles::TypeRole ] = "type";
    roles[ EventsListRoles::TargetRole ] = "target";
    roles[ EventsListRoles::DescriptionRole ] = "description";
    roles[ EventsListRoles::GroupRole ] = "group";

    return roles;
}

void EventsList::setTimeWindow( QSharedPointer< ProcessedData > _data )
{
    BENCHMARK( "EventsList::setTimeWindow()" )

    setCurrentMinimum( _data->currentMinimum() );
    setCurrentMaximum( _data->currentMaximum() );

    m_currentMinimalEpochIndex = _data->minimumEpochIndex();
    m_currentMaximalEpochIndex = _data->maximumEpochIndex();

    invalidateFilter();
}

void EventsList::setEventVisibility( qint32 _id, bool _value )
{
    BENCHMARK( "EventsList::setEventVisibility()" )

    m_eventsTypeMask[ _id ] = _value;

    invalidateFilter();
}

void EventsList::selectAll()
{
    m_eventsTypeMask.fill( true );

    invalidateFilter();
}

void EventsList::deselectAll()
{
    m_eventsTypeMask.fill( false );

    invalidateFilter();
}

EventsList::GROUP_OPERATION EventsList::setGroup( qint32 _id, char _value )
{
    if ( _id < 0 || _id >= m_filteredEvents.size() )
    {
        qCritical().nospace().noquote() << "ERROR: Cannot invoke setGroup() on this element (index = " << _id << ")";
        return GROUP_OPERATION::INVALID;
    }

    char previousGroup = m_filteredEvents[ _id ]->group();

    m_filteredEvents[ _id ]->setGroup( _value );

    QModelIndex index = createIndex( _id, 0 );
    emit dataChanged( index, index );

    if ( previousGroup == ' ' )
    {
        return ( _value == 'A' ) ? GROUP_OPERATION::INC_A : GROUP_OPERATION::INC_B;
    }

    if ( previousGroup == _value )
    {
        return ( _value == 'A' ) ? GROUP_OPERATION::DEC_A : GROUP_OPERATION::DEC_B;
    }

    return ( _value == 'A' ) ? GROUP_OPERATION::INC_A_DEC_B : GROUP_OPERATION::INC_B_DEC_A;
}

void EventsList::clearGroup( char _value )
{
    BENCHMARK( "EventsList::clearGroup()" )

    for ( auto& event : m_events )
    {
        if ( event->group() == _value )
            event->setGroup( ' ' );
    }

    emit dataChanged( createIndex( 0, 0 ), createIndex( m_filteredEvents.size() - 1, 0 ) );
}

QVector< QSharedPointer< Event > > EventsList::group( char _group )
{
    QVector< QSharedPointer< Event > > group;

    for ( auto& event : m_filteredEvents )
    {
        if ( event->group() == _group )
            group.push_back( event );
    }

    return group;
}

qint64 EventsList::currentMinimum() const
{
    return m_currentMinimalEpoch;
}

qint64 EventsList::currentMaximum() const
{
    return m_currentMaximalEpoch;
}

qint64 EventsList::minimumEpoch() const
{
    return m_minimalDateEpoch;
}

qint64 EventsList::maximumEpoch() const
{
    return m_maximalDateEpoch;
}

void EventsList::setCurrentMinimum( qint64 _value )
{
    if ( m_currentMinimalEpoch != _value )
    {
        m_currentMinimalEpoch = _value;

        emit currentMinimumChanged();
    }
}

void EventsList::setCurrentMaximum( qint64 _value )
{
    if ( m_currentMaximalEpoch != _value )
    {
        m_currentMaximalEpoch = _value;

        emit currentMaximumChanged();
    }
}

void EventsList::setMinimumEpoch( qint64 _value )
{
    if ( m_minimalDateEpoch != _value )
    {
        m_minimalDateEpoch = _value;

        emit minimumEpochChanged();
    }
}

void EventsList::setMaximumEpoch( qint64 _value )
{
    if ( m_maximalDateEpoch != _value )
    {
        m_maximalDateEpoch = _value;

        emit maximumEpochChanged();
    }
}

