#ifndef IMIDDLEWARE_H
#define IMIDDLEWARE_H

#include <QSharedPointer>

class Action;

class IMiddleware
{

public:

    virtual ~IMiddleware() = default;

    virtual QSharedPointer< Action > process( QSharedPointer< Action > _action ) = 0;

protected:

    IMiddleware() = default;
    IMiddleware( const IMiddleware& ) = default;
    IMiddleware( IMiddleware&& ) = default;
    IMiddleware& operator=( const IMiddleware& ) = default;
    IMiddleware& operator=( IMiddleware&& ) = default;
};

#endif // IMIDDLEWARE_H
