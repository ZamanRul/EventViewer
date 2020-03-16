QT += quick concurrent svg quickcontrols2

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Refer to the documentation for the
# deprecated API to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS PERF_LOGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        Dispatcher/Action.cpp \
        Dispatcher/ActionProvider.cpp \
        Dispatcher/Dispatcher.cpp \
        Middleware/FileManager.cpp \
        Store/Event.cpp \
        Store/EventFactory.cpp \
        Store/EventTypes.cpp \
        Store/EventsList.cpp \
        Store/Fasades/Charts.cpp \
        Store/Fasades/Data.cpp \
        Store/Fasades/Dialog.cpp \
        Store/Fasades/Filters.cpp \
        Store/Fasades/Status.cpp \
        Store/FilteredEventTypes.cpp \
        Store/MainStore.cpp \
        Store/ProcessedData.cpp \
        Utility/PerformanceLogger.cpp \
        main.cpp

RESOURCES += qml.qrc

RC_ICONS = ev.ico

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    Dispatcher/Action.h \
    Dispatcher/ActionProvider.h \
    Dispatcher/ActionTypes.h \
    Dispatcher/Dispatcher.h \
    Middleware/FileManager.h \
    Middleware/IMiddleware.h \
    Store/Event.h \
    Store/EventFactory.h \
    Store/EventTypes.h \
    Store/EventsList.h \
    Store/Fasades/Charts.h \
    Store/Fasades/Data.h \
    Store/Fasades/Dialog.h \
    Store/Fasades/Filters.h \
    Store/Fasades/Status.h \
    Store/FilteredEventTypes.h \
    Store/IStore.h \
    Store/MainStore.h \
    Store/ProcessedData.h \
    Store/Roles.h \
    Utility/PerformanceLogger.h

DISTFILES +=
