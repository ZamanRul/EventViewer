#include "MainStore.h"

#include "Dispatcher/Action.h"
#include "Dispatcher/ActionTypes.h"

#include <QDebug>
#include <QQmlEngine>

#ifdef PERF_LOGS
    #include "Utility/PerformanceLogger.h"
#endif

MainStore::MainStore() :
    m_status { new Status { } },
    m_dialog { new Dialog { } },
    m_filters { new Filters { } },
    m_charts { new Charts { } },
    m_data { new Data { } },
    m_comparison { new Comparison { } }
{}

void MainStore::process( const QSharedPointer< Action >& _action )
{
    if ( _action.isNull() )
    {
        qCritical().nospace().noquote() << "ERROR: Received action in empty";
        return;
    }

    switch ( _action->type() )
    {
        case ActionType::ShowFileDialog:
            processOpenFileDialog( _action->argument1< bool >() );
            break;

        case ActionType::ShowAboutDialog:
            processOpenAboutDialog( _action->argument1< bool >() );
            break;

        case ActionType::ShowCompareDialog:
            processOpenCompareDialog( _action->argument1< bool >() );
            break;

        case ActionType::RequestFile:
            processRequestFile( _action->argument1< QUrl >() );
            break;

        case ActionType::ProcessFile:
            processFile( _action->argument1< QVariant >(), _action->argument2< QString >(), _action->error() );
            break;

        case ActionType::FilterByTime:
            processFilterByTime( _action->argument1< qint64 >(), _action->argument2< qint64 >() );
            break;

        case ActionType::FilterByEventType:
            processFilterByEventType( _action->argument1< qint32 >(), _action->argument2< bool >() );
            break;

        case ActionType::FilterByEventTypeSelectAll:
            processFilterByEventTypeSelectAll();
            break;

        case ActionType::FilterByEventTypeDeselectAll:
            processFilterByEventTypeDeselectAll();
            break;

        case ActionType::FilterEventTypeName:
            processfilterEventTypeName( _action->argument1< QString >() );
            break;

        case ActionType::AddToGroup:
            processAddToGroup( _action->argument1< qint32 >(), _action->argument2< char >() );
            break;

        case ActionType::ClearGroup:
            processClearGroup( _action->argument1< char >() );
            break;

        default:
            break;
    }
}

void MainStore::processOpenFileDialog( bool _value )
{
    if ( m_dialog.isNull() )
    {
        qCritical().nospace().noquote() << "ERROR: Dialog facade is empty";
        return;
    }

    m_dialog->setShowFileDialog( _value );
}

void MainStore::processOpenAboutDialog( bool _value )
{
    if ( m_dialog.isNull() )
    {
        qCritical().nospace().noquote() << "ERROR: Dialog facade is empty";
        return;
    }

    m_dialog->setShowAboutDialog( _value );
}

void MainStore::processOpenCompareDialog( bool _value )
{
    if ( m_dialog.isNull() )
    {
        qCritical().nospace().noquote() << "ERROR: Dialog facade is empty";
        return;
    }

    if ( m_comparison.isNull() )
    {
        qCritical().nospace().noquote() << "ERROR: Comparison facade is empty";
        return;
    }

    if ( m_data.isNull() )
    {
        qCritical().nospace().noquote() << "ERROR: Data facade is empty";
        return;
    }

    if ( _value == true )
    {
        auto leftGroup = m_data->group( 'A' );
        auto rightGroup = m_data->group( 'B' );

        m_comparison->compare( leftGroup, rightGroup );
    }

    m_dialog->setShowCompareDialog( _value );
}

void MainStore::processRequestFile( const QUrl& _url )
{
    if ( m_status.isNull() )
    {
        qCritical().nospace().noquote() << "ERROR: Status facade is empty";
        return;
    }

    m_status->info( QString( QStringLiteral( "Loading file \"%1\"" ) ).arg( _url.fileName() ) );
}

void MainStore::processFile( const QVariant& _result, const QString& _fileName, bool _errors )
{
    BENCHMARK( "MainStore::processFile()" )

    if ( m_filters.isNull() )
    {
        qCritical().nospace().noquote() << "ERROR: Filters facade is empty";
        return;
    }

    if ( m_status.isNull() )
    {
        qCritical().nospace().noquote() << "ERROR: Status facade is empty";
        return;
    }

    if ( m_data.isNull() )
    {
        qCritical().nospace().noquote() << "ERROR: Data facade is empty";
        return;
    }

    if ( _errors )
    {
        qCritical().nospace().noquote() << "ERROR: " << _result.toString();

        m_status->error( QString { QStringLiteral( "Cannot load requested file. %1" ) }.arg( _result.toString() ) );
        return;
    }

    const QList< QVariant >& _events = _result.value< QList< QVariant > >();

    QVector< QSharedPointer< Event > > events;
    events.reserve( _events.size() );

    for ( const auto& event : _events )
        events << event.value< QSharedPointer< Event > >();

    m_data->registerData( events );

    m_filters->registerData( m_data->processedData() );

    m_charts->setEventsTimeline( m_data->processedData() );

    m_charts->setFilteredEventsTimeline( m_data->processedData() );

    m_status->info( QString( QStringLiteral( "Loaded %1 event(s)" ) ).arg( m_data->affectedEvents() ) );

    m_status->setFileName( _fileName );
}

void MainStore::processFilterByTime( qint64 _minimum, qint64 _maximum )
{
    BENCHMARK( "MainStore::processFilterByTime()" )

    if ( m_filters.isNull() )
    {
        qCritical().nospace().noquote() << "ERROR: Filters facade is empty";
        return;
    }

    if ( m_status.isNull() )
    {
        qCritical().nospace().noquote() << "ERROR: Status facade is empty";
        return;
    }

    if ( m_data.isNull() )
    {
        qCritical().nospace().noquote() << "ERROR: Data facade is empty";
        return;
    }

    m_data->setTimeWindow( _minimum, _maximum );

    m_filters->filterByTime( m_data->processedData() );

    m_status->info( QString { QStringLiteral( "Filtered %1 event(s)" ) }.arg( m_data->affectedEvents() ) );
}

void MainStore::processFilterByEventType( qint32 _id, bool _value )
{
    BENCHMARK( "MainStore::processFilterByEventType()" )

    if ( m_filters.isNull() )
    {
        qCritical().nospace().noquote() << "ERROR: Filters facade is empty";
        return;
    }

    if ( m_status.isNull() )
    {
        qCritical().nospace().noquote() << "ERROR: Status facade is empty";
        return;
    }

    if ( m_data.isNull() )
    {
        qCritical().nospace().noquote() << "ERROR: Data facade is empty";
        return;
    }

    m_data->setEventVisibility( _id, _value );

    m_filters->filterByEventType( _id, _value );

    m_charts->setFilteredEventsTimeline( m_data->processedData() );

    m_status->info( QString { QStringLiteral( "Filtered %1 event(s)" ) }.arg( m_data->affectedEvents() ) );
}

void MainStore::processFilterByEventTypeSelectAll()
{
    BENCHMARK( "MainStore::processFilterByEventTypeSelectAll()" )

    if ( m_filters.isNull() )
    {
        qCritical().nospace().noquote() << "ERROR: Filters facade is empty";
        return;
    }

    if ( m_status.isNull() )
    {
        qCritical().nospace().noquote() << "ERROR: Status facade is empty";
        return;
    }

    if ( m_data.isNull() )
    {
        qCritical().nospace().noquote() << "ERROR: Data facade is empty";
        return;
    }

    m_data->selectAll();

    m_filters->filterByEventTypeSelectAll();

    m_charts->setFilteredEventsTimeline( m_data->processedData() );

    m_status->info( QString { QStringLiteral( "Filtered %1 event(s)" ) }.arg( m_data->affectedEvents() ) );
}

void MainStore::processFilterByEventTypeDeselectAll()
{
    BENCHMARK( "MainStore::processFilterByEventTypeDeselectAll()" )

    if ( m_filters.isNull() )
    {
        qCritical().nospace().noquote() << "ERROR: Filters facade is empty";
        return;
    }

    if ( m_status.isNull() )
    {
        qCritical().nospace().noquote() << "ERROR: Status facade is empty";
        return;
    }

    if ( m_data.isNull() )
    {
        qCritical().nospace().noquote() << "ERROR: Data facade is empty";
        return;
    }

    m_data->deselectAll();

    m_filters->filterByEventTypeDeselectAll();

    m_charts->setFilteredEventsTimeline( m_data->processedData() );

    m_status->info( QString { QStringLiteral( "Filtered %1 event(s)" ) }.arg( m_data->affectedEvents() ) );
}

void MainStore::processfilterEventTypeName( const QString& _value )
{
    BENCHMARK( "MainStore::processfilterEventTypeName()" )

    if ( m_filters.isNull() )
    {
        qCritical().nospace().noquote() << "ERROR: Filters facade is empty";
        return;
    }

    m_filters->filterEventTypeNames( _value );
}

void MainStore::processAddToGroup( qint32 _id, char _value )
{
    if ( m_data.isNull() )
    {
        qCritical().nospace().noquote() << "ERROR: Data facade is empty";
        return;
    }

    m_data->setGroup( _id, _value );
}

void MainStore::processClearGroup( char _value )
{
    if ( m_data.isNull() )
    {
        qCritical().nospace().noquote() << "ERROR: Data facade is empty";
        return;
    }

    m_data->clearGroup( _value );
}

QObject* MainStore::status() const
{
    return m_status.get();
}

QObject* MainStore::dialog() const
{
    return m_dialog.get();
}

QObject* MainStore::filters() const
{
    return m_filters.get();
}

QObject* MainStore::charts() const
{
    return m_charts.get();
}

QObject* MainStore::data() const
{
    return m_data.get();
}

QObject* MainStore::comparison() const
{
    return m_comparison.get();
}

