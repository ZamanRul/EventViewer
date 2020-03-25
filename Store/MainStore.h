#ifndef MAINSTORE_H
#define MAINSTORE_H

#include "IStore.h"

#include "Fasades/Status.h"
#include "Fasades/Dialog.h"
#include "Fasades/Filters.h"
#include "Fasades/Charts.h"
#include "Fasades/Data.h"
#include "Fasades/Comparison.h"

#include <QObject>
#include <QUrl>

class Action;

class MainStore : public QObject, public IStore
{

    Q_OBJECT

    Q_PROPERTY(QObject* status READ status NOTIFY statusGroupChanged)
    Q_PROPERTY(QObject* dialog READ dialog NOTIFY dialogGroupChanged)
    Q_PROPERTY(QObject* filters READ filters NOTIFY filtersGroupChanged)
    Q_PROPERTY(QObject* charts READ charts NOTIFY chartsGroupChanged)
    Q_PROPERTY(QObject* data READ data NOTIFY dataGroupChanged)
    Q_PROPERTY(QObject* comparison READ comparison NOTIFY comparisonGroupChanged)

public:

    MainStore();

    void process( const QSharedPointer< Action >& _action ) override;

public:

    QObject* status() const;
    QObject* dialog() const;
    QObject* filters() const;
    QObject* charts() const;
    QObject* data() const;
    QObject* comparison() const;

signals:

    void statusGroupChanged();
    void dialogGroupChanged();
    void filtersGroupChanged();
    void chartsGroupChanged();
    void dataGroupChanged();
    void comparisonGroupChanged();

private:

    void processOpenFileDialog( bool _value );
    void processFile( const QVariant& _events, const QString& _fileName, bool _errors );
    void processRequestFile( const QUrl& _url );

    void processOpenAboutDialog( bool _value );
    void processOpenCompareDialog( bool _value );

    void processFilterByTime( qint64 _minimum, qint64 _maximum );
    void processFilterByEventType( qint32 _id, bool _value );
    void processFilterByEventTypeSelectAll();
    void processFilterByEventTypeDeselectAll();

    void processfilterEventTypeName( const QString& _value );

    void processAddToGroup( qint32 _id, char _value );
    void processClearGroup( char _value );

private:

    QSharedPointer< Status > m_status;
    QSharedPointer< Dialog > m_dialog;
    QSharedPointer< Filters > m_filters;
    QSharedPointer< Charts > m_charts;
    QSharedPointer< Data > m_data;
    QSharedPointer< Comparison > m_comparison;
};

#endif // MAINSTORE_H
