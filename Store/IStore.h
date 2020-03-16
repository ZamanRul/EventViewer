#ifndef ISTORE_H
#define ISTORE_H

#include <QSharedPointer>

class Action;

class IStore
{
public:

    virtual ~IStore() = default;

    virtual void process( const QSharedPointer< Action >& _action ) = 0;

protected:

    IStore() = default;
    IStore( const IStore& ) = default;
    IStore( IStore&& ) = default;
    IStore& operator=( const IStore& ) = default;
    IStore& operator=( IStore&& ) = default;
};

#endif // ISTORE_H
