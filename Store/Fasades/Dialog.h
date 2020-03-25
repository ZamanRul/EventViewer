#ifndef DIALOGS_H
#define DIALOGS_H

#include <QObject>

class Dialog : public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool showFileDialog READ showFileDialog NOTIFY showFileDialogChanged)
    Q_PROPERTY(bool showAboutDialog READ showAboutDialog NOTIFY showAboutDialogChanged)
    Q_PROPERTY(bool showCompareDialog READ showCompareDialog NOTIFY showCompareDialogChanged)

public:

    Dialog();

    bool showFileDialog() const;
    bool showAboutDialog() const;
    bool showCompareDialog() const;

    void setShowFileDialog( bool _value );
    void setShowAboutDialog( bool _value );
    void setShowCompareDialog( bool _value );

signals:

    void showFileDialogChanged();
    void showAboutDialogChanged();
    void showCompareDialogChanged();

private:

    bool m_showOpenFileDialog;
    bool m_showAboutDialog;
    bool m_showCompareDialog;

};

#endif // DIALOGS_H
