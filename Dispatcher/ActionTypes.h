#ifndef ACTION_TYPES_H
#define ACTION_TYPES_H

enum class ActionType
{
    ShowFileDialog,
    ShowAboutDialog,
    OpenFile,
    RequestFile,
    ProcessFile,
    FilterByTime,
    FilterByEventType,
    FilterByEventTypeSelectAll,
    FilterByEventTypeDeselectAll,
    FilterEventTypeName,
    AddToGroup,
    ClearGroup
};

#endif // ACTION_TYPES_H
