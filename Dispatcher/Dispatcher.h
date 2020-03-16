#ifndef DISPATCHER_H
#define DISPATCHER_H

#include "Middleware/IMiddleware.h"
#include "Store/IStore.h"

#include <QMutex>
#include <QMutexLocker>
#include <QObject>
#include <QQueue>
#include <QtGlobal>
#include <QSharedPointer>
#include <QVector>

class Action;

class Dispatcher final : public QObject
{
    Q_OBJECT

public:

    static Dispatcher& instance();

public:

    void registerMiddleware( QSharedPointer< IMiddleware > _middleware );

    void registerStore( QSharedPointer< IStore > _store );

    void dispatch( QSharedPointer< Action > _action );

signals:

    void newActionAdded();

private:

    Dispatcher();

    Dispatcher( const Dispatcher& ) = delete;
    Dispatcher( Dispatcher&& ) = delete;
    Dispatcher& operator=( const Dispatcher& ) = delete;
    Dispatcher& operator=( Dispatcher&& ) = delete;

    ~Dispatcher() = default;

    void onNewActionAdded();

private:

    QVector< QSharedPointer< IMiddleware > > m_middlewares;
    QVector< QSharedPointer< IStore > > m_stores;

    QQueue< QSharedPointer< Action > > m_actions;

    QMutex m_mutex;
};

#endif // DISPATCHER_H
