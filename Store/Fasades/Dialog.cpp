#include "Dialog.h"

Dialog::Dialog() :
    m_showOpenFileDialog { false },
    m_showAboutDialog { false },
    m_showCompareDialog { false }
{}

bool Dialog::showFileDialog() const
{
    return m_showOpenFileDialog;
}

bool Dialog::showAboutDialog() const
{
    return m_showAboutDialog;
}

bool Dialog::showCompareDialog() const
{
    return m_showCompareDialog;
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

void Dialog::setShowCompareDialog( bool _value )
{
    if ( m_showCompareDialog != _value )
    {
        m_showCompareDialog = _value;

        emit showCompareDialogChanged();
    }
}

