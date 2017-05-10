#include "ChamferedWidget.h"
#include "TextLabel.h"
#include "ErrorIndicator.h"
#include "InputLine.h"
#include <QPainter>
#include <QStyleOption>
#include <QLayout>
#include "Delimeter.h"

ChamferedWidget::ChamferedWidget(QWidget *parent) :
    QWidget(parent)
{
    m_mode    = SemaphoreOff;
    m_isError = false;

    m_textLabel      = new TextLabel;
    m_errorIndicator = new ErrorIndicator;
    m_inputLine      = new InputLine;

    m_layout1 = new QVBoxLayout;
    m_layout2 = new QVBoxLayout;

    m_layout1->setContentsMargins(0, 0, 0, 0);
    m_layout1->setSpacing(0);
    m_layout1->addWidget(m_textLabel);
    m_layout1->addWidget(m_errorIndicator);
    m_layout1->addWidget(m_inputLine);
    m_layout1->setSizeConstraint(QLayout::SetMinimumSize);

    setLayout(m_layout1);

    setStyleSheet(GlobalRes::getQSS());

    connect(m_inputLine, SIGNAL(textEdited(QString)),
            this, SIGNAL(game_inputLineTextEdited(QString)));

    game_setMode(SemaphoreOff);
}

void ChamferedWidget::paintEvent(QPaintEvent* event)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void ChamferedWidget::game_inputLineSetTextSize(int size)
{
    m_inputLine->game_setFontSize(size);
}

void ChamferedWidget::game_textLabelSetTextSize(int size)
{
    m_textLabel->game_setFontSize(size);
}

void ChamferedWidget::game_setTextName(const QString& fontName)
{
    m_inputLine->game_setFontName(fontName);
    m_textLabel->game_setFontName(fontName);
}

void ChamferedWidget::game_inputLineClear()
{
    m_inputLine->clear();
}

void ChamferedWidget::game_textLabelSetTextUnderline(const QString& text, int beg, int end)
{
    m_textLabel->game_setTextUnderline(text, beg, end);
}

void ChamferedWidget::game_setMode(Mode mode)
{
    if (mode == SemaphoreOff)
    {
        m_textLabel->game_setMode(SemaphoreOff);
        m_errorIndicator->show();
        m_inputLine->game_setMode(SemaphoreOff);
        m_inputLine->show();
        m_mode = SemaphoreOff;
    }
    else if (mode == SemaphoreRed)
    {
        if (m_mode != SemaphoreOff)
        {
            qDebug() << "ChamferedWidget is turning to SemaphoreRed but previous mode is not SemaphoreOff";
        }
        m_textLabel->game_setMode(SemaphoreRed);
        m_inputLine->game_setMode(SemaphoreRed);
        m_mode = SemaphoreRed;
    }
    else if (mode == SemaphoreRedAndYellow)
    {
        if (m_mode != SemaphoreRed)
        {
            qDebug() << "ChamferedWidget is turning to SemaphoreRedAndYellow but previous mode is not SemaphoreRed";
        }
        m_textLabel->game_setMode(SemaphoreRedAndYellow);
        m_inputLine->game_setMode(SemaphoreRedAndYellow);
        m_mode = SemaphoreRedAndYellow;
    }
    else if (mode == SemaphoreGreen)
    {
        if (m_mode != SemaphoreRedAndYellow)
        {
            qDebug() << "ChamferedWidget is turning to SemaphoreGreen but previous mode is not SemaphoreRedAndYellow";
        }
        m_textLabel->game_setMode(SemaphoreGreen);
        m_inputLine->game_setMode(SemaphoreGreen);
        m_mode = SemaphoreGreen;
    }
    else if (mode == Finish)
    {
        if (m_mode != SemaphoreGreen)
        {
            qDebug() << "ChamferedWidget is turning to Finish but previous mode is not SemaphoreGreen";
        }

        m_textLabel->game_setMode(Finish);
        m_errorIndicator->hide();
        m_inputLine->game_setMode(Finish);
        m_inputLine->hide();
        m_mode = Finish;
    }
}

void ChamferedWidget::game_setErrorMode(bool isError)
{
    if (m_mode != SemaphoreGreen)
    {
        qDebug() << "ChamferedWidget is trying to set ErrorMode but mode is not SemaphoreGreen";
        return;
    }
    if (isError && !m_isError)
    {
        m_textLabel->game_setErrorMode(true);
        m_errorIndicator->game_setStatus("Error");
        m_inputLine->game_setErrorMode(true);
        m_isError = true;
    }
    else if (!isError && m_isError)
    {
        m_textLabel->game_setErrorMode(false);
        m_errorIndicator->game_setStatus("SemaphoreGreen");
        m_inputLine->game_setErrorMode(false);
        m_isError = false;
    }
}
