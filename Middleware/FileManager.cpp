#include "FileManager.h"

#include "Dispatcher/Action.h"
#include "Dispatcher/ActionProvider.h"
#include "Store/Event.h"
#include "Store/EventFactory.h"
#include "Serialization/EventDeserializer.h"

#include <QFile>
#include <QDataStream>
#include <QDebug>
#include <QUrl>
#include <QtConcurrent>

#ifdef PERF_LOGS
    #include "Utility/PerformanceLogger.h"
#endif

FileManager::FileManager()
{
    QObject::connect( &m_watcher, &QFutureWatcher< QPair< QString, QVariant > >::finished, [ = ] () {
        QPair< QString, QVariant > result = m_watcher.future().result();
        ActionProvider::instance().processFile( result.second, result.first, result.second.isNull() || !result.second.isValid() || result.second.type() == QVariant::String );
    });
}

QSharedPointer< Action > FileManager::process( const QSharedPointer< Action > _action )
{
    if ( _action.isNull() )
    {
        qCritical().nospace().noquote() << "ERROR: Received action in empty";
        return nullptr;
    }

    switch ( _action->type() )
    {
        case ActionType::OpenFile:
        {
            QFuture< QPair< QString, QVariant > > result = QtConcurrent::run( this, &FileManager::processOpenFile, _action->argument1< QUrl >() );
            m_watcher.setFuture( result );

            return QSharedPointer< Action >( new Action( ActionType::RequestFile, _action->argument1< QUrl >() ) );
        }

        default:
            break;
    }

    return _action;
}

QPair< QString, QVariant > FileManager::processOpenFile( const QUrl& _path )
{
    BENCHMARK( "FileManager::processOpenFile()" )

    EventFactory::instance().clear();

    QList< QVariant > events;
    EventDeserializer deserializer;

    auto result = deserializer.deserialize( _path, events );

    if ( result == DESERIALIZATION_RESULT::CANNOT_OPEN_FILE )
    {
        qCritical().nospace().noquote() << "ERROR: Cannot open file '" << _path << "'";
        return qMakePair( _path.fileName(), QVariant { QString { QStringLiteral( "Cannot open file '%1'" ) }.arg( _path.fileName() ) } );
    }

    if ( result == DESERIALIZATION_RESULT::INCORRECT_STAMP )
    {
        qCritical().nospace().noquote() << "ERROR: Requested file has incorrect header";
        return qMakePair( _path.fileName(), QVariant { QStringLiteral( "File has incorrect header" ) } );
    }

    if ( result == DESERIALIZATION_RESULT::INCORRECT_VERSION )
    {
        qCritical().nospace().noquote() << "ERROR: Requested file has incorrect version";
        return qMakePair( _path.fileName(), QVariant { QStringLiteral( "File is in incorrect version" ) } );
    }

    return qMakePair( _path.fileName(), QVariant { events } );
}
