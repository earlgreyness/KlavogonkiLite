#include "TimeWidget.h"
#include <QtGui>

TimeWidget::TimeWidget(QWidget *parent) :
    QLabel(parent)
{
    m_timeout = 10;
    m_time = "";
    setMinimumHeight(91);
    setMaximumHeight(91);
    setAlignment(Qt::AlignVCenter | Qt::AlignLeft);
    game_refreshText();
}

void TimeWidget::game_setTimeout(int secs)
{
    if (secs > 0)
    {
        m_timeout = secs;
    }
}

void TimeWidget::game_setTime(int msecs)
{
    m_time.clear();
    int mins = msecs / (1000 * 60);
    int secs = (msecs / 1000) - mins * 60;
    if (mins < 10)
    {
        m_time += "0";
    }
    m_time += QString::number(mins);
    m_time += ":";
    if (secs < 10)
    {
        m_time += "0";
    }
    m_time += QString::number(secs);
    game_refreshText();
}

void TimeWidget::game_refreshText()
{
    QString pattern = "<style type=\"text/css\">"
              "p { "
              "font-family: Tahoma, Arial;"
              "font-size: 15px;"
            "margin-top: 0px;"
            "margin-bottom: 8px;"
              "}"
              ".bitmore { "
              "font-size: 17px; "
              "}"
              ".mode1 {"
            "color: #4692aa;"
            "}"
              "</style> ";

    QString textBuf = "";
    if (m_mode == SemaphoreRed || m_mode == SemaphoreRedAndYellow)
    {
        textBuf = tr("Start delay") + " ";
    }
    QString text1 = pattern +
                    "<body>"
            "<p><span class=\"mode1\">" + tr("Faultless") + "</span></p>"
            "<p>" + textBuf +
                    "<span class=\"bitmore\">" +
                    m_time +
                    "</span></p>"
                    "</body>";
    if (m_mode == Finish)
    {
        text1 = pattern +
                            "<body>"
                    "<p><span class=\"mode1\">" + tr("Faultless") + "</span></p>"
                    "<p>" + tr("Game end") + "</p>"
                            "</body>";
    }
    setText(text1);
}

void TimeWidget::game_setMode(Mode mode)
{
    if (mode == SemaphoreOff)
    {
        m_mode = SemaphoreOff;
        game_refreshText();
    }
    else if (mode == SemaphoreRed)
    {
        if (m_mode != SemaphoreOff)
        {
            qDebug() << "TimeWidget is turning to SemaphoreRed but previous mode is not SemaphoreOff";
        }
        m_mode = SemaphoreRed;
        game_refreshText();
    }
    else if (mode == SemaphoreRedAndYellow)
    {
        if (m_mode != SemaphoreRed)
        {
            qDebug() << "TimeWidget is turning to SemaphoreRedAndYellow but previous mode is not SemaphoreRed";
        }
        m_mode = SemaphoreRedAndYellow;
        game_refreshText();
    }
    else if (mode == SemaphoreGreen)
    {
        if (m_mode != SemaphoreRedAndYellow)
        {
            qDebug() << "TimeWidget is turning to SemaphoreGreen but previous mode is not SemaphoreRedAndYellow";
        }
        m_mode = SemaphoreGreen;
        game_refreshText();
    }
    else if (mode == Finish)
    {
        if (m_mode != SemaphoreGreen)
        {
            qDebug() << "TimeWidget is turning to Finish but previous mode is not SemaphoreGreen";
        }
        m_mode = Finish;
        game_refreshText();
    }
}

void TimeWidget::game_setDark(bool isDark)
{
}
