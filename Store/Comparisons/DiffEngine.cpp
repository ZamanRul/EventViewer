#include "DiffEngine.h"

#include "DiffLineStatistics.h"

#include <QDebug>

namespace
{
    qint32 similarityCount( const QString& _left, qint32 _leftLow, qint32 _leftHigh, const QString& _right, qint32 _rightLow, qint32 _rightHigh )
    {
        qint32 leftSize = _leftHigh - _leftLow + 1;
        qint32 rightSize = _rightHigh - _rightLow + 1;

        if ( leftSize <= 0 || rightSize <= 0 )
        {
            return 0;
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
            return lcs;
        }

        // Left side of found substring
        lcs += similarityCount( _left, _leftLow, _leftLow + leftEndingIndex - lcs - 1, _right, _rightLow, _rightLow + rightEndingIndex - lcs - 1 );

        // Right side of found substring
        lcs += similarityCount( _left, _leftLow + leftEndingIndex, _leftHigh, _right, _rightLow + rightEndingIndex, _rightHigh );

        return lcs;
    }

    qreal similarityScore( const QString& _left, const QString& _right )
    {
        //  Ratcliff / Obershelp coeficient
        qint32 count = similarityCount( _left, 0, _left.size() - 1, _right, 0, _right.size() - 1 );

        return ( 2.0 * count ) / ( _left.size() + _right.size() );
    }
}

DiffEngine::DiffEngine( const QVector< QPair< QString, qint32 > >& _listA, const QVector< QPair< QString, qint32 > >& _listB ) :
    m_listA { _listA },
    m_listB { _listB }
{}

QVector< DiffLine > DiffEngine::run()
{
    DiffSlice slice { 0, m_listA.size() - 1, 0, m_listB.size() - 1 };

    QVector< DiffLine > lines = diff( slice );

    for ( const auto& line : lines )
    {
        qDebug() << "O: " << static_cast< qint32 >( line.result() ) << " A: " << line.indexA() << " B: " << line.indexB();
    }

    return lines;
}

QVector< DiffLine > DiffEngine::diff( const DiffSlice& _slice )
{
    QVector< DiffLine > lines;

    auto&& matches = findUniqueLines( _slice );

    matches = patienceSort( matches );

    if ( matches.isEmpty() )
    {
        lines.append( fallbackDiff( _slice ) );

        return lines;
    }

    QSharedPointer< DiffLineMatch > match;

    qint32 lineA = _slice.a_low();
    qint32 lineB = _slice.b_low();

    qint32 i = 0;

    while ( i < matches.size() )
    {
        match = matches[ i ];

        DiffSlice subslice { lineA, match->indexA() - 1, lineB, match->indexB() - 1 };

        QVector< DiffLine > sublines = diff( subslice );
        lines.append( sublines );

        lines.push_back( DiffLine { COMPARISION_RESULT::EQUAL, match->indexA(), match->indexB() } );

        lineA = match->indexA() + 1;
        lineB = match->indexB() + 1;

        ++i;
    }

    if ( matches.last()->indexA() < _slice.a_high() || matches.last()->indexB() < _slice.b_high() )
    {
        DiffSlice subslice { matches.last()->indexA() + 1, _slice.a_high(), matches.last()->indexB() + 1, _slice.b_high() };
        lines.append( fallbackDiff( subslice ) );
    }

    return lines;
}

QVector< QSharedPointer< DiffLineMatch > > DiffEngine::findUniqueLines( const DiffSlice& _slice )
{
    QHash< QString, DiffLineStatistics > statistics;
    QVector< QHash< QString, DiffLineStatistics >::iterator > orderedStatistics;

    statistics.reserve( m_listA.size() + m_listB.size() );

    for ( int a = _slice.a_low(); a <= _slice.a_high(); ++a )
    {
        if ( !statistics.contains( m_listA[ a ].first ) )
            orderedStatistics.push_back( statistics.insert( m_listA[ a ].first, DiffLineStatistics { } ) );

        statistics[ m_listA[ a ].first ].registerForA( a );
    }

    for ( int b = _slice.b_low(); b <= _slice.b_high(); ++b )
    {
        if ( !statistics.contains( m_listB[ b ].first ) )
            orderedStatistics.push_back( statistics.insert( m_listB[ b ].first, DiffLineStatistics { } ) );

        statistics[ m_listB[ b ].first ].registerForB( b );
    }

    QVector< QSharedPointer< DiffLineMatch > > matches;

    for ( const auto& statisticIterator : orderedStatistics )
    {
        auto&& statistic = *statisticIterator;
        if ( statistic.countA() == 1 && statistic.countB() == 1 )
        {
            matches.push_back( QSharedPointer< DiffLineMatch > { new DiffLineMatch { statistic.indexA(), statistic.indexB() } } );
        }
    }

    return matches;
}

QVector< QSharedPointer< DiffLineMatch > > DiffEngine::patienceSort( const QVector< QSharedPointer< DiffLineMatch > >& _matches )
{
    QVector< QSharedPointer< DiffLineMatch > > stacks;

    for ( auto& match : _matches )
    {
        int i = 0;
        for ( ; i < stacks.size(); ++i )
        {
            if ( stacks[ i ]->indexB() > match->indexB() )
            {
                stacks[ i ] = match;
                break;
            }
        }

        if ( i == stacks.size() )
        {
            stacks.push_back( match );
        }

        if ( i != 0 )
        {
            match->setPrevious( stacks[ i - 1 ] );
        }
    }

    QVector< QSharedPointer< DiffLineMatch > > lis;

    if ( !stacks.isEmpty() )
    {
        QSharedPointer< DiffLineMatch > item = stacks.last();

        while ( item != nullptr )
        {
            lis.push_back( item );

            item = item->previous();
        }
    }

    std::reverse( lis.begin(), lis.end() );

    return lis;
}

QVector< DiffLine > DiffEngine::fallbackDiff( const DiffSlice& _slice )
{
    const qreal threshold = 0.7;

    QVector< DiffLine > lines;

    bool found = false;

    qint32 previousB = _slice.b_low();
    qreal equalityScore = 0;

    for ( qint32 a = _slice.a_low(); a <= _slice.a_high(); ++a )
    {
        found = false;

        for ( qint32 b = previousB; b <= _slice.b_high() && !found; ++b )
        {
            equalityScore = similarityScore( m_listA[ a ].first, m_listB[ b ].first );
            if ( m_listA[ a ].second == m_listB[ b ].second && equalityScore >= threshold )
            {
                for ( int i = previousB; i < b; ++i )
                {
                    lines.push_back( DiffLine { COMPARISION_RESULT::ONLY_RIGHT, -1, i } );
                }

                lines.push_back( DiffLine { equalityScore == 1.0 ? COMPARISION_RESULT::EQUAL : COMPARISION_RESULT::SIMILAR, a, b } );

                previousB = b + 1;

                found = true;
            }
        }

        if ( found == false )
        {
            lines.push_back( DiffLine { COMPARISION_RESULT::ONLY_LEFT, a, -1 } );
        }
    }

    for ( int i = previousB; i <= _slice.b_high(); ++i )
    {
        lines.push_back( DiffLine { COMPARISION_RESULT::ONLY_RIGHT, -1, i } );
    }

    return lines;
}
