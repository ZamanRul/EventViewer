#include "Dialog.h"

Dialog::Dialog() :
    m_showOpenFileDialog { false },
    m_showAboutDialog { false }
{}

bool Dialog::showFileDialog() const
{
    return m_showOpenFileDialog;
}

bool Dialog::showAboutDialog() const
{
    return m_showAboutDialog;
}

void Dialog::setShowFileDialog( bool _value )
{
    if ( m_showOpenFileDialog != _value )
    {
        m_showOpenFileDialog = _value;

        emit showFileDialogChanged();
    }
}

void Dialog::setShowAboutDialog( bool _value )
{
    if ( m_showAboutDialog != _value )
    {
        m_showAboutDialog = _value;

        emit showAboutDialogChanged();
    }
}
