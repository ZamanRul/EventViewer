#ifndef ROLES_H
#define ROLES_H

#include <QEvent>

enum EventsListRoles {
    TimeRole = Qt::UserRole + 1,
    EpochRole,
    TypeIdRole,
    TypeRole,
    TargetRole,
    DescriptionRole,
    GroupRole
};

enum EventTypesRoles {
    NullRole = Qt::UserRole + 1,
    IdRole,
    NameRole,
    OccurenceRole,
    VisibleRole
};

enum CompareEventsRoles {
    OperationTypeRole = Qt::UserRole + 1,
    EventTypeRole,
    TimeLeftRole,
    TargetLeftRole,
    DescriptionLeftRole,
    TimeRightRole,
    TargetRightRole,
    DescriptionRightRole,
};

#endif // ROLES_H
