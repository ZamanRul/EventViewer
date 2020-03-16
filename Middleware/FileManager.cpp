#include "FileManager.h"

#include "Dispatcher/Action.h"
#include "Dispatcher/ActionProvider.h"
#include "Store/Event.h"
#include "Store/EventFactory.h"

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

    QFile file( _path.toLocalFile() );

    if ( !file.open( QIODevice::ReadOnly ) )
    {
        qCritical().nospace().noquote() << "ERROR: Cannot open file '" << _path << "'";
        return qMakePair( _path.fileName(), QVariant { QString { QStringLiteral( "Cannot open file '%1'" ) }.arg( _path.fileName() ) } );
    }

    QDataStream stream( &file );

    const quint32 constantMagicNumber = 0xA0B0C0D1;

    quint32 magicNumber = 0;
    qint64 epoch = 0;
    qint32 type = 0;
    QString target;
    QString description;

    QList< QVariant > events;

    stream >> magicNumber;

    if ( magicNumber != constantMagicNumber )
    {
        qCritical().nospace().noquote() << "ERROR: Requested file has incorrect header";
        return qMakePair( _path.fileName(), QVariant { QStringLiteral( "File has incorrect header" ) } );
    }

    EventFactory::instance().clear();

    while ( !stream.atEnd() )
    {
        stream >> epoch
                >> type
                >> target
                >> description;

        events.push_back( QVariant::fromValue( EventFactory::instance().create( epoch, type, target, description ) ) );
    }

    return qMakePair( _path.fileName(), QVariant { events } );
}
