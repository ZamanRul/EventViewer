#include "CompareEventsModel.h"

#include "../Roles.h"

CompareEventsModel::~CompareEventsModel()
{
    beginResetModel();

    m_eventsRows.clear();

    endResetModel();
}

void CompareEventsModel::registerData( const QVector< QSharedPointer< CompareEventsRow > >& _data )
{
    beginResetModel();

    m_eventsRows.clear();
    m_eventsRows = _data;

    endResetModel();
}

int CompareEventsModel::rowCount( const QModelIndex& _parent ) const
{
    Q_UNUSED( _parent )

    return m_eventsRows.size();
}

QVariant CompareEventsModel::data( const QModelIndex& _index, int _role ) const
{
    if ( _index.row() < 0 || _index.row() >= m_eventsRows.size() )
        return QVariant { };

    if ( _role == CompareEventsRoles::OperationTypeRole )
        return static_cast< qint32 > ( m_eventsRows[ _index.row() ]->rowMode() );
    else if ( _role == CompareEventsRoles::EventTypeRole  )
        return m_eventsRows[ _index.row() ]->type();
    else if ( _role == CompareEventsRoles::TimeLeftRole  )
        return m_eventsRows[ _index.row() ]->dateLeft();
    else if ( _role == CompareEventsRoles::TargetLeftRole  )
        return m_eventsRows[ _index.row() ]->targetLeft();
    else if ( _role == CompareEventsRoles::DescriptionLeftRole  )
        return m_eventsRows[ _index.row() ]->descriptionLeft();
    else if ( _role == CompareEventsRoles::TimeRightRole  )
        return m_eventsRows[ _index.row() ]->dateRight();
    else if ( _role == CompareEventsRoles::TargetRightRole  )
        return m_eventsRows[ _index.row() ]->targetRight();
    else if ( _role == CompareEventsRoles::DescriptionRightRole  )
        return m_eventsRows[ _index.row() ]->descriptionRight();
    else
        return QVariant { };
}

QHash< int, QByteArray > CompareEventsModel::roleNames() const
{
    QHash< int, QByteArray > roles;

    roles[ OperationTypeRole ] = "operation";
    roles[ CompareEventsRoles::EventTypeRole ] = "type";
    roles[ CompareEventsRoles::TimeLeftRole ] = "leftTime";
    roles[ CompareEventsRoles::TargetLeftRole ] = "leftTarget";
    roles[ CompareEventsRoles::DescriptionLeftRole ] = "leftDescription";
    roles[ CompareEventsRoles::TimeRightRole ] = "rightTime";
    roles[ CompareEventsRoles::TargetRightRole ] = "rightTarget";
    roles[ CompareEventsRoles::DescriptionRightRole ] = "rightDescription";

    return roles;
}
