#ifndef STATUS_H
#define STATUS_H

#include <QObject>
#include <QMutex>

class Status : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString state READ state NOTIFY stateChanged)
    Q_PROPERTY(QString message READ message NOTIFY messageChanged)
    Q_PROPERTY(QString fileName READ fileName NOTIFY fileNameChanged)

public:

    Status();

    QString state() const;
    QString message() const;
    QString fileName() const;

    void info( const QString& _message = QStringLiteral( "" ) );
    void warning( const QString& _message = QStringLiteral( "" ) );
    void error( const QString& _message = QStringLiteral( "" ) );

    void setFileName( const QString& _fileName = QStringLiteral( "" ) );

signals:

    void stateChanged();
    void messageChanged();
    void fileNameChanged();

private:

    void setState( const QString& _state );
    void setMessage( const QString& _message );

private:

    QMutex m_mutex;

    QString m_state;
    QString m_message;

    QString m_fileName;

};

#endif // STATUS_H
