#ifndef SMART_H
#define SMART_H

#include "GlobDef.h"
#include <QObject>

class QWidget;
class QLabel;
class QTimer;
class QVBoxLayout;
class QPushButton;
class ChamferedWidget;
class TimeWidget;
class Semaphore;
class Speedometer;
class FinishTrack;
class StartWidget;
class RaceServiceInfo;

class Game : public QObject
{
    Q_OBJECT

public:
    Game();
    void moveToCenter(QWidget* w);

private:
    //Widgets:    
    QWidget*         widget;
    QPushButton*     startButton;
    Semaphore*       semaphore;
    TimeWidget*      timeWidget;
    QLabel*          timeLabel;
    Speedometer*     speedometer;
    ChamferedWidget* chamferedWidget;
    FinishTrack*     finishTrack;

    StartWidget*     startWidget;

    //Members:
    RaceServiceInfo* m_info;
    Mode             m_mode;
    bool             m_dark;
    QTimer*          m_timer1;
    QTimer*          m_timer2;
    QTimer*          m_timer3;

    QVBoxLayout* mainLayout;
    QVBoxLayout* mainLayout2;
    QVBoxLayout* superPuperLayout;

private:
    void game_setMode(Mode mode);
    void game_setDark(bool);
    void game_setErrorMode(bool);

private slots:
    void game_beginGame();
    void slotTextEditedInLineEdit(const QString&);
    void slotTimeRightOut();
    void slotTimeLeftOut();

    void game_check1();
    void game_check2();
    void game_check3();
    void game_change(const QString&);
};

#endif // SMART_H
