#ifndef ACTIONPROVIDER_H
#define ACTIONPROVIDER_H

#include <QObject>
#include <QString>
#include <QVariant>

class ActionProvider final : public QObject
{
    Q_OBJECT

public:

    static ActionProvider& instance();

public:

    Q_INVOKABLE void showFileDialog( bool _show );
    Q_INVOKABLE void openFile( const QUrl& _path );
    Q_INVOKABLE void processFile( QVariant _data, const QString& _fileName, bool _error = false );

    Q_INVOKABLE void showAboutDialog( bool _show );
    Q_INVOKABLE void showCompareDialog( bool _show );

    Q_INVOKABLE void filterByTime( qint64 _minimum, qint64 _maximum );
    Q_INVOKABLE void filterByEventType( qint32 _id, bool _value );
    Q_INVOKABLE void filterByEventTypeSelectAll();
    Q_INVOKABLE void filterByEventTypeDeselectAll();

    Q_INVOKABLE void filterEventTypeName( const QString& _value );

    Q_INVOKABLE void addToGroup( qint32 _id, char _value );
    Q_INVOKABLE void clearGroup( char _value );

private:

    ActionProvider() = default;
    ActionProvider( const ActionProvider& ) = delete;
    ActionProvider( ActionProvider&& ) = delete;
    ActionProvider& operator=( const ActionProvider& ) = delete;
    ActionProvider& operator=( ActionProvider&& ) = delete;

    ~ActionProvider() = default;
};

#endif // ACTIONPROVIDER_H
