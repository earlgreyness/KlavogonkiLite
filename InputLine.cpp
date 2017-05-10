#include "InputLine.h"

InputLine::InputLine(QWidget *parent) :
    QLineEdit(parent)
{
    m_mode = SemaphoreOff;
    m_isError = false;
    m_fontSize = 25;
    m_fontName = "tahoma";
    game_setMode(SemaphoreOff);
}

QString InputLine::game_getStatus() const
{
    return game_status;
}

void InputLine::game_setStatus(QString status)
{
    game_status = status;
    setStyleSheet(GlobalRes::getQSS());
    setStyleSheet(
                ".InputLine {"
                "font-family: " + m_fontName + "; " +
                "font-size: " + QString::number(m_fontSize) + "px;" +
                "}");
}

void InputLine::game_refreshStyleSheet()
{
    if (m_mode == SemaphoreOff || m_mode == SemaphoreRed || m_mode == SemaphoreRedAndYellow || m_mode == Finish)
    {
        game_setStatus("SemaphoreOff");
        qDebug() << "setting status SemOff";
    }
    else if (m_mode == SemaphoreGreen)
    {
        if (m_isError)
        {
            game_setStatus("Error");
            qDebug() << "setting status Error";
        }
        else
        {
            game_setStatus("SemaphoreGreen");
            qDebug() << "setting status SemGreen";
        }
    }
}

void InputLine::game_setMode(Mode mode)
{
    if (mode == SemaphoreOff)
    {
        m_mode = SemaphoreOff;
        game_refreshStyleSheet();
        setMaxLength(32767);
        setText(tr("prelabel"));
        setCursorPosition(0);
        setEnabled(false);
    }
    else if (mode == SemaphoreRed)
    {
        if (m_mode != SemaphoreOff)
        {
            qDebug() << "InputLine is turning to SemaphoreRed but previous mode is not SemaphoreOff";
        }
        m_mode = SemaphoreRed;
        game_refreshStyleSheet();
    }
    else if (mode == SemaphoreRedAndYellow)
    {
        if (m_mode != SemaphoreRed)
        {
            qDebug() << "InputLine is turning to SemaphoreRedAndYellow but previous mode is not SemaphoreRed";
        }
        m_mode = SemaphoreRedAndYellow;
        game_refreshStyleSheet();
    }
    else if (mode == SemaphoreGreen)
    {
        if (m_mode != SemaphoreRedAndYellow)
        {
            qDebug() << "InputLine is turning to SemaphoreGreen but previous mode is not SemaphoreRedAndYellow";
        }
        m_mode = SemaphoreGreen;
        game_refreshStyleSheet();
        setMaxLength(30);
        setText("");
        setEnabled(true);
        setFocus();        
    }
    else if (mode == Finish)
    {
        if (m_mode != SemaphoreGreen)
        {
            qDebug() << "InputLine is turning to Finish but previous mode is not SemaphoreGreen";
        }
        m_mode = Finish;
        game_refreshStyleSheet();
        setMaxLength(32767);
        setText("");
        setEnabled(false);               
    }
}

void InputLine::game_setErrorMode(bool isError)
{
    m_isError = isError;
    game_refreshStyleSheet();
}

void InputLine::game_setFontName(const QString& fontName)
{
    if (fontName != m_fontName)
    {
        m_fontName = fontName;
        game_setStatus(game_status);
    }
}

void InputLine::game_setFontSize(int fontSize)
{
    if (fontSize != m_fontSize)
    {
        m_fontSize = fontSize;
        game_setStatus(game_status);
    }
}
