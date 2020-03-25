#include "Comparison.h"

#include "../Comparisons/CompareEventsRow.h"
#include "../Comparisons/DiffEngine.h"

#include <QStringBuilder>

#ifdef PERF_LOGS
    #include "Utility/PerformanceLogger.h"
#endif

namespace
{

    void findDifferences( const QString& _left, QVector< bool >& _leftMask, qint32 _leftLow, qint32 _leftHigh, const QString& _right, QVector< bool >& _rightMask, qint32 _rightLow, qint32 _rightHigh )
    {
        qint32 leftSize = _leftHigh - _leftLow + 1;
        qint32 rightSize = _rightHigh - _rightLow + 1;

        if ( leftSize <= 0 || rightSize <= 0 )
        {
            return;
        }

        QVector< qint32 > matrix ( ( leftSize + 1 ) * ( rightSize + 1 ), 0 );

        qint32 lcs = 0;
        qint32 leftEndingIndex = 0;
        qint32 rightEndingIndex = 0;

        for ( int i = 1; i <= leftSize; ++i )
        {
            for ( int j = 1; j <= rightSize; ++j )
            {
                if ( _left[ _leftLow + i - 1 ] == _right[ _rightLow + j - 1 ] )
                {
                    matrix[ i * ( rightSize + 1 ) + j ] = matrix[ ( i - 1 ) * ( rightSize + 1 ) + j - 1 ] + 1;

                    if ( matrix[ i * ( rightSize + 1 ) + j ] > lcs )
                    {
                        lcs = matrix[ i * ( rightSize + 1 ) + j ];
                        leftEndingIndex = i;
                        rightEndingIndex = j;
                    }
                }
            }
        }

        if ( lcs == 0 )
        {
            return;
        }

        for ( int i = _leftLow + leftEndingIndex - lcs; i < _leftLow + leftEndingIndex; ++i )
            _leftMask[ i ] = true;

        for ( int i = _rightLow + rightEndingIndex - lcs; i < _rightLow + rightEndingIndex; ++i )
            _rightMask[ i ] = true;

        // Left side of found substring
        findDifferences( _left, _leftMask, _leftLow, _leftLow + leftEndingIndex - lcs - 1, _right, _rightMask, _rightLow, _rightLow + rightEndingIndex - lcs - 1 );

        // Right side of found substring
        findDifferences( _left, _leftMask, _leftLow + leftEndingIndex, _leftHigh, _right, _rightMask, _rightLow + rightEndingIndex, _rightHigh );
    }

    QString highlightChanges( const QString& _originalString, const QVector< bool >& _mask )
    {
        const QString highlightBegin { QStringLiteral( "<font color=\"#ff004a\"><b><u>" ) };
        const QString highlightEnd { QStringLiteral( "</u></b></font>" ) };

        QString result;

        bool highlight = false;

        for ( int i = 0; i < _originalString.size(); ++i  )
        {
            if ( _mask[ i ] )
            {
                if ( highlight == true )
                {
                    result = result % highlightEnd;
                    highlight = false;
                }

                result = result % _originalString[ i ];
            }
            else
            {
                if ( highlight == false )
                {
                    result = result % highlightBegin;
                    highlight = true;
                }

                result = result % _originalString[ i ];
            }
        }

        if ( highlight == true )
            result = result % highlightEnd;

        return result;
    }

    void showDifferences( QString& _left, QString& _right )
    {
        QVector< bool > leftMask( _left.size(), false );
        QVector< bool > rightMask( _right.size(), false );

        findDifferences( _left, leftMask, 0, _left.size() -1, _right, rightMask, 0, _right.size() - 1 );

        _left = highlightChanges( _left, leftMask );
        _right = highlightChanges( _right, rightMask );
    }
}


Comparison::Comparison() :
    m_compareEventsModel { new CompareEventsModel { } }
{}

QObject* Comparison::compareEventsModel() const
{
    return m_compareEventsModel.get();
}

void Comparison::compare( QVector< QSharedPointer< Event > >& _leftGroup, QVector< QSharedPointer< Event > >& _rightGroup )
{
    BENCHMARK( "Comparison::compare()" )

    auto translatedLeftGroup = prepareGroupToCompare( _leftGroup );
    auto translatedRightGroup = prepareGroupToCompare( _rightGroup );

    DiffEngine engine { translatedLeftGroup, translatedRightGroup };

    QVector< DiffLine > lines = engine.run();

    auto rows = createCompareRows( lines, _leftGroup, _rightGroup );
    m_compareEventsModel->registerData( rows );
};

QVector< QPair< QString, qint32 > > Comparison::prepareGroupToCompare( const QVector< QSharedPointer< Event > >& _group )
{
    QVector< QPair< QString, qint32 > > translatedGroup;

    for ( auto& event : _group )
    {
        QString translatedEvent { QStringLiteral( "" ) };
        translatedEvent = translatedEvent  % event->typeName() % ";" % event->target() % ";" % event->description();

        translatedGroup.push_back( qMakePair( translatedEvent, event->type() ) );
    }

    return translatedGroup;
}

QVector< QSharedPointer< CompareEventsRow > > Comparison::createCompareRows( const QVector< DiffLine >& _lines,
                                                                             const QVector< QSharedPointer< Event > >& _leftGroup,
                                                                             const QVector< QSharedPointer< Event > >& _rightGroup )
{
    QVector< QSharedPointer< CompareEventsRow > > rows;

    for ( auto& line : _lines )
    {
       if ( line.result() == COMPARISION_RESULT::EQUAL )
       {
           rows.push_back( QSharedPointer< CompareEventsRow >{ new CompareEventsRow { line.result(),
                                                                                        _leftGroup[ line.indexA() ]->typeName(),
                                                                                        _leftGroup[ line.indexA() ]->dateTime(),
                                                                                        _leftGroup[ line.indexA() ]->target(),
                                                                                        _leftGroup[ line.indexA() ]->description(),
                                                                                        _rightGroup[ line.indexB() ]->dateTime(),
                                                                                        _rightGroup[ line.indexB() ]->target(),
                                                                                        _rightGroup[ line.indexB() ]->description()} } );
       }
       else if ( line.result() == COMPARISION_RESULT::SIMILAR )
       {
           QString targetLeft = _leftGroup[ line.indexA() ]->target();
           QString targetRight = _rightGroup[ line.indexB() ]->target();

           showDifferences( targetLeft, targetRight );

           QString descriptionLeft = _leftGroup[ line.indexA() ]->description();
           QString descriptionRight = _rightGroup[ line.indexB() ]->description();

           showDifferences( descriptionLeft, descriptionRight );

           rows.push_back( QSharedPointer< CompareEventsRow >{ new CompareEventsRow { line.result(),
                                                                                        _leftGroup[ line.indexA() ]->typeName(),
                                                                                        _leftGroup[ line.indexA() ]->dateTime(),
                                                                                        targetLeft,
                                                                                        descriptionLeft,
                                                                                        _rightGroup[ line.indexB() ]->dateTime(),
                                                                                        targetRight,
                                                                                        descriptionRight} } );
       }
       else if ( line.result() == COMPARISION_RESULT::ONLY_LEFT )
       {
           rows.push_back( QSharedPointer< CompareEventsRow >{ new CompareEventsRow { line.result(),
                                                                                        _leftGroup[ line.indexA() ]->typeName(),
                                                                                        _leftGroup[ line.indexA() ]->dateTime(),
                                                                                        _leftGroup[ line.indexA() ]->target(),
                                                                                        _leftGroup[ line.indexA() ]->description(),
                                                                                        QStringLiteral( "" ),
                                                                                        QStringLiteral( "" ),
                                                                                        QStringLiteral( "" )} } );
       }
       else if ( line.result() == COMPARISION_RESULT::ONLY_RIGHT )
       {
           rows.push_back( QSharedPointer< CompareEventsRow >{ new CompareEventsRow { line.result(),
                                                                                        _rightGroup[ line.indexB() ]->typeName(),
                                                                                        QStringLiteral( "" ),
                                                                                        QStringLiteral( "" ),
                                                                                        QStringLiteral( "" ),
                                                                                        _rightGroup[ line.indexB() ]->dateTime(),
                                                                                        _rightGroup[ line.indexB() ]->target(),
                                                                                        _rightGroup[ line.indexB() ]->description() } } );
       }
    }

    return rows;
}


