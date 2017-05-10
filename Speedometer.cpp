#include "Speedometer.h"
#include <QPainter>
#include <cmath>

Speedometer::Speedometer(QWidget *parent) :
    QWidget(parent)
{
    m_dark = false;
    m_mode = SemaphoreOff;

    m_labelSpeed = 0;
    m_arrowSpeed = 0;
    m_numErrors = 0;

    pixmapArrow.load(":/images/speedometerArrow.png");
    pixmapPanelTop.load(":/images/speedometerPanelTop.png");
    pixmapPanel.load(":/images/speedometerPanel.png");
    pixmapDarkBackground.load(":/images/speedometerBlack.png");

    setAutoFillBackground(true);
    resize(262, 91);
    setMinimumSize(262, 91);
    setMaximumSize(262, 91);

    game_setMode(SemaphoreOff);
}

void Speedometer::game_setDark(bool dark)
{
    m_dark = dark;
    this->update();
}

void Speedometer::game_setMode(Mode mode)
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
            qDebug() << "Speedometer is turning to SemaphoreRed but previous mode is not SemaphoreOff";
        }        
        m_labelSpeed = 0;
        m_arrowSpeed = 0;
        m_numErrors = 0;
        m_mode = SemaphoreRed;
        this->update();
    }
    else if (mode == SemaphoreRedAndYellow)
    {
        if (m_mode != SemaphoreRed)
        {
            qDebug() << "Speedometer is turning to SemaphoreRedAndYellow but previous mode is not SemaphoreRed";
        }
        m_mode = SemaphoreRedAndYellow;
        this->update();
    }
    else if (mode == SemaphoreGreen)
    {
        if (m_mode != SemaphoreRedAndYellow)
        {
            qDebug() << "Speedometer is turning to SemaphoreGreen but previous mode is not SemaphoreRedAndYellow";
        }
        m_mode = SemaphoreGreen;
        this->update();
    }
    else if (mode == Finish)
    {
        if (m_mode != SemaphoreGreen)
        {
            qDebug() << "Speedometer is turning to Finish but previous mode is not SemaphoreGreen";
        }
        m_mode = Finish;
        this->update();
    }

}

void Speedometer::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.drawPixmap(0, 0, pixmapPanel);
    if (m_mode == SemaphoreGreen || m_mode == Finish)
    {
        // 262x91
        int w = 86; // 7x39
        int h = 66;
        painter.save();
        painter.translate(w, h);
        painter.rotate(game_angle(m_arrowSpeed));
        painter.setRenderHint(QPainter::SmoothPixmapTransform);
        painter.drawPixmap(0, 26 - h, pixmapArrow);
        painter.restore();
        painter.drawPixmap(0, 0, pixmapPanelTop);
        painter.setPen(QColor(255, 255,255));
        painter.setFont(QFont("Tahoma", 18, QFont::Normal));
        painter.drawText(185, 64, QString::number(m_numErrors));
        painter.setFont(QFont("Tahoma", 13, QFont::Normal));
        int labelWidth;
        if (m_labelSpeed < 10)
        {
            labelWidth = 83;
        }
        else if (m_labelSpeed < 100)
        {
            labelWidth = 78;
        }
        else
        {
            labelWidth = 74;
        }
        painter.drawText(labelWidth, 79, QString::number((int)m_labelSpeed));

    }
    if (m_dark)
    {
        painter.setCompositionMode(QPainter::CompositionMode_Multiply);
        painter.drawPixmap(0, 0, pixmapDarkBackground);
    }
}

double Speedometer::game_angle(double speed)
{
    double maxSpeed = 800;
    if (speed > maxSpeed)
    {
        speed = maxSpeed;
    }
    return ((4.90 - 3.05) * speed / maxSpeed + 3.05) * 90;
}

void Speedometer::game_setLabelSpeed(double speed)
{
    m_labelSpeed = speed;
    this->update();
}

void Speedometer::game_setArrowSpeed(double speed)
{
    m_arrowSpeed = speed;
    this->update();
}

void Speedometer::game_setNumErrors(int numErrors)
{
    m_numErrors = numErrors;
    this->update();
}
