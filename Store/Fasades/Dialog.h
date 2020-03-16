#ifndef DIALOGS_H
#define DIALOGS_H

#include <QObject>

class Dialog : public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool showFileDialog READ showFileDialog NOTIFY showFileDialogChanged)
    Q_PROPERTY(bool showAboutDialog READ showAboutDialog NOTIFY showAboutDialogChanged)

public:

    Dialog();

    bool showFileDialog() const;
    bool showAboutDialog() const;

    void setShowFileDialog( bool _value );
    void setShowAboutDialog( bool _value );

signals:

    void showFileDialogChanged();
    void showAboutDialogChanged();

private:

    bool m_showOpenFileDialog;
    bool m_showAboutDialog;

};

#endif // DIALOGS_H
