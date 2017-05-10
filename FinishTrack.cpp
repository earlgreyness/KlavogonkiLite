#include "FinishTrack.h"
#include <QPainter>
#include <QLabel>

FinishTrack::FinishTrack(QWidget *parent) :
    QWidget(parent)
{
    car.load(":/images/car.png");
    m_carPosition = 0.0;
    m_dark = false;
    setAutoFillBackground(true);
    this->resize(740, 125);
    setMinimumSize(740, 125);
    setMaximumSize(740, 125);
    pixmap.load(":/images/finishTrackWhite.png");
    pixmapBlack.load(":/images/finishTrackBlack.png");
    label1 = new QLabel(this);
    label2 = new QLabel(this);
    label3 = new QLabel(this);
    pattern = "<style type=\"text/css\">"
              " BODY { "
              "font-family: Tahoma, Arial;"
              "font-size: 16px"
              "}"
              ".bitmore { "
              "font-size: 19px; "
              "}"
              "</style> ";

}

TimeResult FinishTrack::game_getTimeResult(int msecs)
{
    TimeResult time;
    int dsecsTotal = (msecs % 100 >= 50) ? msecs / 100 + 1
                                         : msecs / 100;
    int mins  = (dsecsTotal / 10) / 60;
    int secs  = (dsecsTotal - (mins * 60 * 10)) / 10;
    int dsecs = (dsecsTotal - (mins * 60 * 10) - secs * 10);
    time.mins = QString::number(mins);
    if (time.mins.size() == 1)
    {
        time.mins = "0" + time.mins;
    }
    time.secs = QString::number(secs);
    if (time.secs.size() == 1)
    {
        time.secs = "0" + time.secs;
    }
    time.dsecs = QString::number(dsecs);
    return time;
}

QString FinishTrack::game_getSpeedResult(int numSymbols, int msecs)
{
    qreal speedDouble = (qreal)numSymbols / (((qreal)msecs / 1000.0) / 60.0);
    int speed = (speedDouble - (qreal)((int)speedDouble) > 0.500) ? (int)speedDouble + 1
                                                                   : (int)speedDouble;
    return QString::number(speed);
}

QString FinishTrack::game_getErrorsPercentResult(int numSymbols, int numErrors)
{
    qreal errorsDouble = (qreal)numErrors / (qreal)numSymbols * 100;
    QString errorsPercent = QString::number(errorsDouble, 'f', 2);
    for (int i = 0; i < errorsPercent.size(); ++i)
    {
        if (errorsPercent[i] == '.')
        {
            errorsPercent[i] = ',';
            break;
        }
    }
    return errorsPercent;
}

void FinishTrack::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.drawPixmap(0, 0, pixmap);

    int position = (int)((this->size().width() - 24 - 11 - car.size().width()) * (m_carPosition / 100.));
    painter.drawPixmap(position, 84, car);

    if (m_dark)
    {
        painter.setCompositionMode(QPainter::CompositionMode_Multiply);
        painter.drawPixmap(0, 0, pixmapBlack);
    }
}

void FinishTrack::game_setCarPosition(double percent)
{
    if (percent >= 0.0 && percent <= 100.0)
    {
        m_carPosition = percent;
    }
    this->update();
}

void FinishTrack::game_setMode(Mode mode)
{
    if (mode == SemaphoreOff)
    {
        label1->hide();
        label2->hide();
        label3->hide();
        m_carPosition = 0.0;
        m_mode = SemaphoreOff;
    }
    else if (mode == SemaphoreRed)
    {
        if (m_mode != SemaphoreOff)
        {
            qDebug() << "FinishTrack is turning to SemaphoreRed but previous mode is not SemaphoreOff";
        }
        m_carPosition = 0.0;
        m_mode = SemaphoreRed;
    }
    else if (mode == SemaphoreRedAndYellow)
    {
        if (m_mode != SemaphoreRed)
        {
            qDebug() << "FinishTrack is turning to SemaphoreRedAndYellow but previous mode is not SemaphoreRed";
        }
        m_mode = SemaphoreRedAndYellow;
    }
    else if (mode == SemaphoreGreen)
    {
        if (m_mode != SemaphoreRedAndYellow)
        {
            qDebug() << "FinishTrack is turning to SemaphoreGreen but previous mode is not SemaphoreRedAndYellow";
        }
        m_mode = SemaphoreGreen;
    }
    else if (mode == Finish)
    {
        if (m_mode != SemaphoreGreen)
        {
            qDebug() << "FinishTrack is turning to Finish but previous mode is not SemaphoreGreen";
        }

        int n = 19;

        QString text1 = pattern +
                        "<body>"
                        "<span class=\"bitmore\">" +
                        result.time.mins + ":" + result.time.secs +
                        "</span>" + "." + result.time.dsecs +
                        "</body>";
        QString text2 = pattern +
                        "<body>"
                        "<span class=\"bitmore\">" +
                        result.speed +
                        "</span> " + tr("symbols per minute") +
                        "</body>";
        QString text3 = pattern +
                        "<body>"
                        "<span class=\"bitmore\">" +
                        result.errors +
                        "</span> " +
                        tr("mistake", "", result.errors.toInt()) +
                        " (<span class=\"bitmore\">" +
                        result.errorsPercent +
                        "</span>%)"
                        "</body>";

        label1->setText(text1);
        label2->setText(text2);
        label3->setText(text3);

        label1->resize(label1->sizeHint());
        label2->resize(label2->sizeHint());
        label3->resize(label3->sizeHint());

        label1->move(160, 104 - n);
        label2->move(243, 104 - n);
        label3->move(350, 104 - n);

        label1->show();
        label2->show();
        label3->show();

        m_mode = Finish;
    }
}

void FinishTrack::game_setDark(bool dark)
{
    m_dark = dark;
    this->update();
}

void FinishTrack::game_setResults(int numSymbols, int msecs, int numerrors)
{
    result.time          = game_getTimeResult(msecs);
    result.speed         = game_getSpeedResult(numSymbols, msecs);
    result.errorsPercent = game_getErrorsPercentResult(numSymbols, numerrors);
    result.errors        = QString::number(numerrors);
}
