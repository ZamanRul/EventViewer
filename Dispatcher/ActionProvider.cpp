#include "ActionProvider.h"

#include "Action.h"
#include "Dispatcher.h"
#include "ActionTypes.h"

ActionProvider& ActionProvider::instance()
{
    static ActionProvider self;
    return self;
}

void ActionProvider::showFileDialog( bool _show )
{
    Dispatcher::instance().dispatch( QSharedPointer< Action >( new Action( ActionType::ShowFileDialog, _show ) ) );
}

void ActionProvider::openFile( const QUrl& _path )
{
    Dispatcher::instance().dispatch( QSharedPointer< Action >( new Action( ActionType::OpenFile, _path ) ) );
}

void ActionProvider::processFile( QVariant _data, const QString& _fileName, bool _error )
{
    QVariant fileName { _fileName };
    Dispatcher::instance().dispatch( QSharedPointer< Action >( new Action( ActionType::ProcessFile, _data, fileName, _error ) ) );
}

void ActionProvider::showAboutDialog( bool _show )
{
    Dispatcher::instance().dispatch( QSharedPointer< Action >( new Action( ActionType::ShowAboutDialog, _show ) ) );
}

void ActionProvider::filterByTime( qint64 _minimum, qint64 _maximum )
{
    Dispatcher::instance().dispatch( QSharedPointer< Action >( new Action( ActionType::FilterByTime, _minimum, _maximum ) ) );
}

void ActionProvider::filterByEventType( qint32 _id, bool _value )
{
    Dispatcher::instance().dispatch( QSharedPointer< Action >( new Action( ActionType::FilterByEventType, _id, _value ) ) );
}

void ActionProvider::filterByEventTypeSelectAll()
{
    Dispatcher::instance().dispatch( QSharedPointer< Action >( new Action( ActionType::FilterByEventTypeSelectAll ) ) );
}

void ActionProvider::filterByEventTypeDeselectAll()
{
    Dispatcher::instance().dispatch( QSharedPointer< Action >( new Action( ActionType::FilterByEventTypeDeselectAll ) ) );
}

void ActionProvider::filterEventTypeName( const QString& _value )
{
    Dispatcher::instance().dispatch( QSharedPointer< Action >( new Action( ActionType::FilterEventTypeName, _value ) ) );
}

void ActionProvider::addToGroup( qint32 _id, char _value )
{
    Dispatcher::instance().dispatch( QSharedPointer< Action >( new Action( ActionType::AddToGroup, _id, _value ) ) );
}

void ActionProvider::clearGroup( char _value )
{
    Dispatcher::instance().dispatch( QSharedPointer< Action >( new Action( ActionType::ClearGroup, _value ) ) );
}
