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

#endif // ROLES_H
