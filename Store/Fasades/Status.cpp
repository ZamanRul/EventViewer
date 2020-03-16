#include "Status.h"

#include <QMutexLocker>

namespace {
    const QString INFO_STATE = QStringLiteral( "info" );
    const QString WARNING_STATE = QStringLiteral( "warning" );
    const QString ERROR_STATE = QStringLiteral( "error" );
}

Status::Status() :
    m_state { INFO_STATE },
    m_message { QStringLiteral( "" ) }
{}

void Status::info( const QString& _message )
{
    QMutexLocker locker( &m_mutex );

    setState( INFO_STATE );
    setMessage( _message );
}

void Status::warning( const QString& _message )
{
    QMutexLocker locker( &m_mutex );

    setState( WARNING_STATE );
    setMessage( _message );
}
void Status::error( const QString& _message )
{
    QMutexLocker locker( &m_mutex );

    setState( ERROR_STATE );
    setMessage( _message );
}

QString Status::state() const
{
    return m_state;
}

QString Status::message() const
{
    return m_message;
}

QString Status::fileName() const
{
    return m_fileName;
}

void Status::setState( const QString& _state )
{
    if ( m_state != _state )
    {
        m_state = _state;

        emit stateChanged();
    }
}

void Status::setMessage( const QString& _message )
{
    if ( m_message != _message )
    {
        m_message = _message;

        emit messageChanged();
    }
}

void Status::setFileName( const QString& _fileName )
{
    if ( m_fileName != _fileName )
    {
        m_fileName = _fileName;

        emit fileNameChanged();
    }
}
