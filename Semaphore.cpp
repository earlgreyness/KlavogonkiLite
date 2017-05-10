#include "Semaphore.h"
#include <QPainter>

Semaphore::Semaphore(QWidget *parent) :
    QWidget(parent)
{
    m_dark = false;
    m_mode = SemaphoreOff;
    pixmapOff.load(":/images/semaphorOffWhite.png");
    pixmapRed.load(":/images/semaphorRedWhite.png");
    pixmapRedAndYellow.load(":/images/semaphorRedandyellowWhite.png");
    pixmapGreen.load(":/images/semaphorGreenWhite.png");
    pixmapDarkBackground.load(":/images/semaphorBlack.png");

    this->setAutoFillBackground(true);
    this->resize(59, 91);
    setMinimumSize(59, 91);
    setMaximumSize(59, 91);

    game_setMode(SemaphoreOff);
}

void Semaphore::game_setDark(bool dark)
{
    m_dark = dark;
    this->update();
}

void Semaphore::game_setMode(Mode mode)
{
    if (mode == SemaphoreOff)
    {
        m_mode = SemaphoreOff;
        this->update();
    }
    else if (mode == SemaphoreRed)
    {
        if (m_mode != SemaphoreOff)
        {
            qDebug() << "Semaphore is turning to SemaphoreRed but previous mode is not SemaphoreOff";
        }
        m_mode = SemaphoreRed;
        this->update();
    }
    else if (mode == SemaphoreRedAndYellow)
    {
        if (m_mode != SemaphoreRed)
        {
            qDebug() << "Semaphore is turning to SemaphoreRedAndYellow but previous mode is not SemaphoreRed";
        }
        m_mode = SemaphoreRedAndYellow;
        this->update();
    }
    else if (mode == SemaphoreGreen)
    {
        if (m_mode != SemaphoreRedAndYellow)
        {
            qDebug() << "Semaphore is turning to SemaphoreGreen but previous mode is not SemaphoreRedAndYellow";
        }
        m_mode = SemaphoreGreen;
        this->update();
    }
    else if (mode == Finish)
    {
        if (m_mode != SemaphoreGreen)
        {
            qDebug() << "Semaphore is turning to Finish but previous mode is not SemaphoreGreen";
        }
        m_mode = Finish;
        this->update();
    }

}

void Semaphore::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    if (m_mode == SemaphoreOff)
    {
        painter.drawPixmap(0, 0, pixmapOff);
    }
    else if (m_mode == SemaphoreRed)
    {
        painter.drawPixmap(0, 0, pixmapRed);
    }
    else if (m_mode == SemaphoreRedAndYellow)
    {
        painter.drawPixmap(0, 0, pixmapRedAndYellow);
    }
    else if (m_mode == SemaphoreGreen)
    {
        painter.drawPixmap(0, 0, pixmapGreen);
    }
    else if (m_mode == Finish)
    {
        painter.drawPixmap(0, 0, pixmapGreen);
    }

    if (m_dark)
    {
        // и решение было найдено! отлично!
        painter.setCompositionMode(QPainter::CompositionMode_Multiply);
        painter.drawPixmap(0, 0, pixmapDarkBackground);
    }
}
