#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include "IMiddleware.h"

#include <QFutureWatcher>

class FileManager : public IMiddleware
{

public:

    FileManager();

    QSharedPointer< Action > process( QSharedPointer< Action > _action ) override;

private:

    QPair< QString, QVariant > processOpenFile( const QUrl& _path );

private:

    QFutureWatcher< QPair< QString, QVariant > > m_watcher;

};

#endif // FILEMANAGER_H
