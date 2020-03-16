#ifdef PERF_LOGS

#include "PerformanceLogger.h"

PerfomanceLogger::PerfomanceLogger( const QString& _scopeName ) :
    m_scopeName { _scopeName },
    m_timer {}
{
    m_timer.start();
}

PerfomanceLogger::~PerfomanceLogger()
{
    qDebug() << "PERFORMANCE: " << m_scopeName << ": " << m_timer.elapsed() << " ms.";
}

#endif
