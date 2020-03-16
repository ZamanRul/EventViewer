#include "Action.h"

Action::Action( ActionType _type, QVariant& _argument_1, QVariant& _argument_2, bool _error ) :
    m_type { _type },
    m_argument_1 { _argument_1 },
    m_argument_2 { _argument_2 },
    m_error { _error }
{}

Action::Action( ActionType _type, QVariant&& _argument_1, QVariant&& _argument_2, bool _error ) :
    m_type { _type },
    m_argument_1 { std::move( _argument_1 ) },
    m_argument_2 { std::move( _argument_2 ) },
    m_error { _error }
{}

ActionType Action::type() const
{
    return m_type;
}

bool Action::error() const
{
    return m_error;
}
