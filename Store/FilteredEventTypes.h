#ifndef FILTEREDEVENTTYPES_H
#define FILTEREDEVENTTYPES_H

#include <QSortFilterProxyModel>

class FilteredEventTypes : public QSortFilterProxyModel
{
    Q_OBJECT

public:

    FilteredEventTypes();

    void filterNames( const QString& _value );

protected:

    bool filterAcceptsRow( int _sourceRow, const QModelIndex& _sourceParent ) const override;

    bool lessThan( const QModelIndex& _left, const QModelIndex& _right ) const override;


private:

    QString m_pattern;
};

#endif // FILTEREDEVENTTYPES_H
