#ifndef ACTION_H
#define ACTION_H

#include "ActionTypes.h"

#include <QVariant>

class Action final
{

public:

    Action( ActionType _type, QVariant& _argument_1, QVariant& _argument_2, bool _error = false );
    Action( ActionType _type, QVariant&& _argument_1 = QVariant { }, QVariant&& _argument_2 = QVariant { }, bool _error = false );

    Action( const Action& ) = default;
    Action( Action&& ) = default;
    Action& operator=( const Action& ) = default;
    Action& operator=( Action&& ) = default;

    ~Action() = default;

    ActionType type() const;

    template< class T >
    T argument1() const;

    template< class T >
    T argument2() const;

    bool error() const;

private:

    ActionType m_type;

    QVariant m_argument_1;
    QVariant m_argument_2;

    bool m_error;
};

template< class T >
T Action::argument1() const
{
    return qvariant_cast< T >( m_argument_1 );
}

template< class T >
T Action::argument2() const
{
    return qvariant_cast< T >( m_argument_2 );
}

#endif // ACTION_H
