#ifndef PERFORMANCELOGGER_H
#define PERFORMANCELOGGER_H

#ifdef PERF_LOGS

#include <QDebug>
#include <QElapsedTimer>

class PerfomanceLogger
{

public:

    PerfomanceLogger( const QString& _scopeName );

    ~PerfomanceLogger();

private:

    QString m_scopeName;
    QElapsedTimer m_timer;

};

#define BENCHMARK(scope) PerfomanceLogger logger { QStringLiteral( scope ) };

#else

#define BENCHMARK(scope)

#endif

#endif // PERFORMANCELOGGER_H
