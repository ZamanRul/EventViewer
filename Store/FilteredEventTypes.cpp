#include "FilteredEventTypes.h"

#include "Roles.h"

FilteredEventTypes::FilteredEventTypes() :
    QSortFilterProxyModel {},
    m_pattern {}
{}

void FilteredEventTypes::filterNames( const QString& _value )
{
    if ( m_pattern != _value )
    {
        m_pattern = _value;

        invalidateFilter();
    }
}

bool FilteredEventTypes::filterAcceptsRow( int _sourceRow, const QModelIndex& _sourceParent ) const
{
    QModelIndex index = sourceModel()->index( _sourceRow, 0, _sourceParent );

    if ( sourceModel()->data( index, EventTypesRoles::NullRole ).toBool() )
        return false;

    if ( !m_pattern.isEmpty() && !sourceModel()->data( index, EventTypesRoles::NameRole ).toString().contains( m_pattern, Qt::CaseInsensitive ) )
        return false;

    return true;
}

bool FilteredEventTypes::lessThan( const QModelIndex& _left, const QModelIndex& _right ) const
{
    qint32 leftOccurrence = sourceModel()->data( _left, EventTypesRoles::OccurenceRole ).toInt();
    qint32 rightOccurrence = sourceModel()->data( _right,  EventTypesRoles::OccurenceRole ).toInt();

    if ( leftOccurrence > 0 && rightOccurrence <= 0 )
        return true;
    else if ( leftOccurrence <= 0 && rightOccurrence > 0 )
        return false;
    else
    {
        qint32 leftId = sourceModel()->data( _left, EventTypesRoles::IdRole ).toInt();
        qint32 rightId = sourceModel()->data( _right, EventTypesRoles::IdRole ).toInt();

        return leftId < rightId;
    }
}
