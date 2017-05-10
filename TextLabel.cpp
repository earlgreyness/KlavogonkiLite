#include "TextLabel.h"

TextLabel::TextLabel(QWidget *parent) :
    QLabel(parent)
{
    m_mode = SemaphoreOff;
    game_status = "SemaphoreOff";
    m_isError = false;
    m_fontName = "tahoma";
    m_fontSize = 17;
    m_text = "";
    m_beg = 0;
    m_end = 0;
    setWordWrap(true);
    game_setMode(SemaphoreOff);
}

QString TextLabel::game_getStatus() const
{
    return game_status;
}

void TextLabel::game_setStatus(QString status)
{
    game_status = status;
    setStyleSheet(GlobalRes::getQSS());
    setStyleSheet(
                ".TextLabel {"
                "font-family: " + m_fontName + "; " +
                "font-size: " + QString::number(m_fontSize) + "px;" +
                "}");
}

void TextLabel::game_refreshStyleSheet()
{
    if (m_mode == SemaphoreOff || m_mode == SemaphoreRed)
    {
        game_setStatus("SemaphoreOff");
    }
    else if (m_mode == SemaphoreRedAndYellow || m_mode == Finish)
    {
        game_setStatus("SemaphoreRedAndYellow");
    }
    else if (m_mode == SemaphoreGreen)
    {
        game_setStatus("SemaphoreGreen");
    }
}

void TextLabel::game_refreshText()
{
    if (m_beg < 0 || m_end > m_text.size() || m_beg > m_end)
    {
        qDebug() << "TextLabel : text iterators error :" << "m_beg =" << m_beg << ", m_end =" << m_end << ", m_text.size() =" << m_text.size();
        qDebug() << "TextLabel : setting m_beg = 0, m_end = 0";
        m_beg = 0;
        m_end = 0;
    }
    if (m_beg != m_end && m_mode == SemaphoreGreen)
    {
        setText(
                m_text.left(m_beg)
                + (m_isError ? "<FONT COLOR=#FF0000><U>" : "<FONT COLOR=#3333AA><U>")
                + m_text.mid(m_beg, m_end - m_beg)
                + "</U></FONT>"
                + m_text.right(m_text.size() - m_end));
    }
    else
    {
        setText(m_text);
    }
}

void TextLabel::game_setTextUnderline(const QString& text, int beg, int end)
{
    m_text = text;
    m_beg = beg;
    m_end = end;
    game_refreshText();
}

void TextLabel::game_setErrorMode(bool isError)
{
    m_isError = isError;
    game_refreshText();
}

void TextLabel::game_setMode(Mode mode)
{
    if (mode == SemaphoreOff)
    {
        m_mode = SemaphoreOff;
        game_refreshStyleSheet();
        setText("<p align=\"center\">" + tr("Text holder") + "</p>");
    }
    else if (mode == SemaphoreRed)
    {
        if (m_mode != SemaphoreOff)
        {
            qDebug() << "TextLabel is turning to SemaphoreRed but previous mode is not SemaphoreOff";
        }
        m_mode = SemaphoreRed;
        game_refreshStyleSheet();
    }
    else if (mode == SemaphoreRedAndYellow)
    {
        if (m_mode != SemaphoreRed)
        {
            qDebug() << "TextLabel is turning to SemaphoreRedAndYellow but previous mode is not SemaphoreRed";
        }
        m_mode = SemaphoreRedAndYellow;
        game_refreshStyleSheet();
        setText("");
    }
    else if (mode == SemaphoreGreen)
    {
        if (m_mode != SemaphoreRedAndYellow)
        {
            qDebug() << "TextLabel is turning to SemaphoreGreen but previous mode is not SemaphoreRedAndYellow";
        }
        m_mode = SemaphoreGreen;
        game_refreshStyleSheet();
    }
    else if (mode == Finish)
    {
        if (m_mode != SemaphoreGreen)
        {
            qDebug() << "TextLabel is turning to Finish but previous mode is not SemaphoreGreen";
        }
        m_mode = Finish;
        game_refreshStyleSheet();
        setText("<p align=\"center\">" + tr("Eour type is customary") + "</p>");
    }
}

void TextLabel::game_setFontName(const QString& fontName)
{
    if (fontName != m_fontName)
    {
        m_fontName = fontName;
        game_setStatus(game_status);
    }
}

void TextLabel::game_setFontSize(int fontSize)
{
    if (fontSize != m_fontSize)
    {
        m_fontSize = fontSize;
        game_setStatus(game_status);
    }
}
