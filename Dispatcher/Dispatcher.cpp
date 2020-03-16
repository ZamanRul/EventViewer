#include "Dispatcher.h"

Dispatcher& Dispatcher::instance()
{
    static Dispatcher instance;
    return instance;
}

Dispatcher::Dispatcher()
{
    QObject::connect( this, &Dispatcher::newActionAdded, this, &Dispatcher::onNewActionAdded, Qt::QueuedConnection );
}

void Dispatcher::registerMiddleware( QSharedPointer< IMiddleware > _middleware )
{
    m_middlewares.push_back( _middleware );
}

void Dispatcher::registerStore( QSharedPointer< IStore > _store )
{
    m_stores.push_back( _store );
}

void Dispatcher::dispatch( QSharedPointer< Action > _action )
{
    QMutexLocker locker( &m_mutex );

    m_actions.enqueue( _action );

    emit newActionAdded();
}

void Dispatcher::onNewActionAdded()
{
    m_mutex.lock();

    while ( !m_actions.empty() )
    {
        auto action = m_actions.dequeue();

        m_mutex.unlock();

        for ( const auto& middleware : m_middlewares )
        {
            action = middleware->process( action );
        }

        for ( const auto& store : m_stores )
        {
            store->process( action );
        }

        m_mutex.lock();
    }

    m_mutex.unlock();
}
