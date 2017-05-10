#include "Smart.h"
#include <QLabel>
#include <QTimer>
#include <QPushButton>
#include <QDesktopWidget>
#include <QLayout>
#include <QApplication>
#include "ChamferedWidget.h"
#include "TimeWidget.h"
#include "StartWidget.h"
#include "FinishTrack.h"
#include "Semaphore.h"
#include "Speedometer.h"
#include "SettingsWidget.h"
#include "RaceServiceInfo.h"

Game::Game()
{    
//    qsrand(QTime(0, 0, 0, 0).secsTo(QTime::currentTime()));
    m_mode = SemaphoreOff;
    m_dark = true;
    m_info = new RaceServiceInfo;

    widget          = new QWidget;
    semaphore       = new Semaphore;
    timeWidget      = new TimeWidget;
    speedometer     = new Speedometer;
    finishTrack     = new FinishTrack;
    chamferedWidget = new ChamferedWidget;
    startWidget     = new StartWidget;

    QHBoxLayout* topLayout = new QHBoxLayout;
    topLayout->setSpacing(0);
    topLayout->addWidget(semaphore);
    topLayout->addSpacing(1);
    topLayout->addWidget(timeWidget);
    topLayout->addWidget(speedometer);
    topLayout->setSizeConstraint(QLayout::SetFixedSize);
    topLayout->setContentsMargins(0, 0, 0, 0);

    startButton = new QPushButton;
    startButton->setText(tr("start"));
    mainLayout = new QVBoxLayout;
    mainLayout->setSpacing(0);
    mainLayout->addLayout(topLayout);
    mainLayout->addSpacing(14);
    mainLayout->addWidget(chamferedWidget);

    connect(startButton, SIGNAL(clicked()),
            this, SLOT(game_beginGame()));

    mainLayout->addSpacing(14);
    mainLayout->addWidget(finishTrack);
    mainLayout->setAlignment(finishTrack, Qt::AlignHCenter);

    mainLayout->addStretch();
    mainLayout->setAlignment(Qt::AlignCenter);
    mainLayout->setSizeConstraint(QLayout::SetMinAndMaxSize);
    mainLayout->setContentsMargins(30, 30, 30, 0);

    widget->setWindowTitle(tr("title"));

    connect(chamferedWidget, SIGNAL(game_inputLineTextEdited(QString)),
            this, SLOT(slotTextEditedInLineEdit(QString)));

    m_info->game_initStringsFromFile("3.txt");
    game_setMode(SemaphoreOff);

    m_timer1 = new QTimer;
    m_timer2 = new QTimer;
    m_timer3 = new QTimer;

    mainLayout2 = new QVBoxLayout;
    mainLayout2->addWidget(startWidget);


    widget->setLayout(mainLayout);

    connect(startWidget, SIGNAL(startGameButtonClicked()), this, SLOT(game_beginGame()));

    startWidget->show();
    moveToCenter(startWidget);

    qDebug() << "chamferedWidget : " << chamferedWidget->size().width();
    qDebug() << "chamferedWidget : hint :" << chamferedWidget->sizeHint().width();
    m_info->m_time.start();
}

void Game::game_beginGame()
{
    startWidget->hide();
    widget->show();
    widget->setMinimumHeight(widget->sizeHint().height() + 50);
    moveToCenter(widget);
    m_info->resetAll();
    game_setMode(SemaphoreOff);
    m_info->game_selectRandomString();
    m_info->game_selectNextWord();
    game_setMode(SemaphoreRed);
    m_info->m_flag = false;
    connect(m_info->m_timer, SIGNAL(timeout()), this, SLOT(slotTimeLeftOut()));
    m_info->m_timer->start(250);
    m_info->m_time.restart();
}

void Game::slotTimeLeftOut()
{
    int msecs = m_info->m_timeLeft - m_info->m_time.elapsed();
    int seconds = msecs / 1000;
    if (seconds > 0)
    {
        timeWidget->game_setTime(msecs);
        if (seconds < 3 && !m_info->m_flag)
        {
            game_setMode(SemaphoreRedAndYellow);
            chamferedWidget->game_textLabelSetTextUnderline(m_info->m_strings[m_info->m_curStringNum], 0, 0);
            m_info->m_flag = true;
        }
    }
    else
    {
        disconnect(m_info->m_timer, SIGNAL(timeout()), this, SLOT(slotTimeLeftOut()));
        game_setMode(SemaphoreGreen);
        timeWidget->game_setTime(0);
        chamferedWidget->game_textLabelSetTextUnderline(m_info->m_strings[m_info->m_curStringNum], m_info->m_beg, m_info->m_end - 1);
        connect(m_info->m_timer, SIGNAL(timeout()), this, SLOT(slotTimeRightOut()));
        m_info->m_timer->start(250);
        m_info->m_time.restart();

        m_timer1->start(100);
        m_timer2->start(1000);
        m_timer3->start(3000);
        connect(m_timer1, SIGNAL(timeout()), this, SLOT(game_check1()));
        connect(m_timer2, SIGNAL(timeout()), this, SLOT(game_check2()));
        connect(m_timer3, SIGNAL(timeout()), this, SLOT(game_check3()));
    }
}

void Game::slotTimeRightOut()
{
    int msecs = m_info->m_time.elapsed();
    timeWidget->game_setTime(msecs);
}

void Game::slotTextEditedInLineEdit(const QString& str)
{
    game_change(str);
    QString curWord = m_info->m_strings[m_info->m_curStringNum].mid(m_info->m_beg, m_info->m_end - m_info->m_beg);

    if (game_isStringsEqual(str, curWord))
    {
        if (m_info->m_isError)
        {
            game_setErrorMode(false);
        }
        //speedometer->game_setLabelSpeed((double)m_info->m_end * 60000 / m_info->m_time.elapsed());
        //speedometer->game_setArrowSpeed((double)m_info->m_end * 60000 / m_info->m_time.elapsed());
        chamferedWidget->game_inputLineClear();

        finishTrack->game_setCarPosition((double)m_info->m_end / m_info->m_strings[m_info->m_curStringNum].size() * 100.0);

        m_info->game_selectNextWord();
        if (m_info->m_beg == m_info->m_strings[m_info->m_curStringNum].size())
        {
            int msecs = m_info->m_time.elapsed();
            disconnect(m_info->m_timer, SIGNAL(timeout()), this, SLOT(slotTimeRightOut()));
            chamferedWidget->game_textLabelSetTextUnderline(m_info->m_strings[m_info->m_curStringNum], 0, 0);

            finishTrack->game_setResults(m_info->m_strings[m_info->m_curStringNum].size(), msecs, m_info->m_numErrors);
            game_setMode(Finish);
           // disconnect(m_timer1, SIGNAL(timeout()), this, SLOT(game_check1()));
         //   disconnect(m_timer2, SIGNAL(timeout()), this, SLOT(game_check2()));
         //   disconnect(m_timer3, SIGNAL(timeout()), this, SLOT(game_check3()));

            //game_beginGame();
        }
        else
        {
            chamferedWidget->game_textLabelSetTextUnderline(m_info->m_strings[m_info->m_curStringNum], m_info->m_beg, m_info->m_end - 1);
        }
    }
    else
    {
        if (!game_isStringsEqual(str, curWord.left(str.size())))
        {
            if (!m_info->m_isError)
            {
                game_setErrorMode(true);
                ++m_info->m_numErrors;
                speedometer->game_setNumErrors(m_info->m_numErrors);
            }
        }
        else if (m_info->m_isError)
        {
            game_setErrorMode(false);
        }
    }
}

void Game::game_setErrorMode(bool ok)
{
    chamferedWidget->game_setErrorMode(ok);
    m_info->m_isError = ok;
}

void Game::game_setDark(bool dark)
{
    semaphore->game_setDark(dark);
    speedometer->game_setDark(dark);
    finishTrack->game_setDark(dark);
    m_dark = dark;
}

void Game::game_setMode(Mode mode)
{
    if (mode == SemaphoreOff)
    {
        chamferedWidget->game_setMode(SemaphoreOff);
        semaphore->game_setDark(false);
        semaphore->game_setMode(SemaphoreOff);
        speedometer->game_setDark(false);
        speedometer->game_setMode(SemaphoreOff);
        finishTrack->game_setDark(false);
        finishTrack->game_setMode(SemaphoreOff);
        timeWidget->game_setMode(SemaphoreOff);
        widget->setStyleSheet(".QWidget {background-color: #FFFFFF;}");
        m_mode = SemaphoreOff;
    }
    else if (mode == SemaphoreRed)
    {
        if (m_mode != SemaphoreOff)
        {
            qDebug() << "Game is turning to SemaphoreRed but previous mode is not SemaphoreOff";
        }
        chamferedWidget->game_setMode(SemaphoreRed);
        semaphore->game_setMode(SemaphoreRed);
        speedometer->game_setMode(SemaphoreRed);
        finishTrack->game_setMode(SemaphoreRed);
        timeWidget->game_setMode(SemaphoreRed);
        startButton->setEnabled(false);
        m_mode = SemaphoreRed;
    }
    else if (mode == SemaphoreRedAndYellow)
    {
        if (m_mode != SemaphoreRed)
        {
            qDebug() << "Game is turning to SemaphoreRedAndYellow but previous mode is not SemaphoreRed";
        }
        chamferedWidget->game_setMode(SemaphoreRedAndYellow);
        semaphore->game_setMode(SemaphoreRedAndYellow);
        speedometer->game_setMode(SemaphoreRedAndYellow);
        finishTrack->game_setMode(SemaphoreRedAndYellow);
        timeWidget->game_setMode(SemaphoreRedAndYellow);
        m_mode = SemaphoreRedAndYellow;
    }
    else if (mode == SemaphoreGreen)
    {
        if (m_mode != SemaphoreRedAndYellow)
        {
            qDebug() << "Game is turning to SemaphoreGreen but previous mode is not SemaphoreRedAndYellow";
        }        
        chamferedWidget->game_setMode(SemaphoreGreen);
        semaphore->game_setMode(SemaphoreGreen);
        semaphore->game_setDark(m_dark);
        speedometer->game_setMode(SemaphoreGreen);
        speedometer->game_setDark(m_dark);
        finishTrack->game_setMode(SemaphoreGreen);
        finishTrack->game_setDark(m_dark);
        timeWidget->game_setMode(SemaphoreGreen);
        if (m_dark)
        {
            widget->setStyleSheet(".QWidget {background-color: #7F7F7F;}");
        }
        else
        {
            widget->setStyleSheet(".QWidget {background-color: #FFFFFF;}");
        }
        m_mode = SemaphoreGreen;
    }
    else if (mode == Finish)
    {
        if (m_mode != SemaphoreGreen)
        {
            qDebug() << "Game is turning to Finish but previous mode is not SemaphoreGreen";
        }
        chamferedWidget->game_setMode(Finish);
        semaphore->game_setDark(false);
        semaphore->game_setMode(Finish);
        finishTrack->game_setDark(false);
        finishTrack->game_setMode(Finish);
        speedometer->game_setDark(false);
        speedometer->game_setMode(Finish);
        timeWidget->game_setMode(Finish);
        widget->setStyleSheet(".QWidget {background-color: #FFFFFF;}");
        startButton->setEnabled(true);
        m_mode = Finish;
    }
}

void Game::moveToCenter(QWidget* w)
{
    w->move(qApp->desktop()->availableGeometry(w).center() - w->rect().center());
}

void Game::game_check1() // launch every 100 msecs
{
    m_info->mspeedArrow = m_info->mspeedArrow * 0.9 + m_info->mspeed * 0.1;
    speedometer->game_setArrowSpeed(m_info->mspeedArrow);
}

void Game::game_check2() // launch every 1000 msecs
{
    speedometer->game_setLabelSpeed(m_info->mspeedArrow);
}

void Game::game_check3() // launch every 3000 msecs
{
    QDateTime c = QDateTime::currentDateTime();
    if (m_info->lastTimePressed.msecsTo(c) > 2000)
    {
        m_info->mspeed = 0;
    }
}

void Game::game_change(const QString& f)
{
    if (m_mode != SemaphoreGreen)
    {
        return;
    }
    ++m_info->pressedNum;
    QDateTime d = QDateTime::currentDateTime();
    if (m_info->pressedNum >= m_info->lastPressedNum + 3 && f.size() != m_info->lastLength)
    {
        if (!m_info->lastTimePressed.isNull())
        {
            double g = 0.25;
            double c = 60 * 1000 * 3 / m_info->lastTimePressed.msecsTo(d);
            m_info->mspeed = m_info->mspeed * (1 - g) + c * g;
        }
        m_info->lastTimePressed = d;
        m_info->lastPressedNum = m_info->pressedNum;
    }
    m_info->lastLength = f.size();
}
