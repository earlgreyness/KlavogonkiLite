#ifndef RACESERVICEINFO_H
#define RACESERVICEINFO_H

#include "GlobDef.h"
#include <QTime>
#include <QDateTime>

class QTimer;


class RaceServiceInfo : public QObject
{
public:
    explicit RaceServiceInfo(QObject *parent = 0);
    void resetAll();
    void game_selectRandomString();
    void game_initStringsFromFile(const QString& fileName);
    void game_selectNextWord();

public:
    QVector<QString> m_strings;
    QVector<int>     m_recentNumbers;
    int              m_curStringNum;

    int              m_beg;
    int              m_end;
    bool             m_isError;
    int              m_numErrors;

    QTimer*          m_timer;
    QTime            m_time;
    int              m_timeLeft;
    bool             m_flag;

    double  mspeed;
    double  mspeedArrow;
   // int     lastTimePressed;

    QDateTime lastTimePressed;
    int     lastLength;
    int     pressedNum;
    int     lastPressedNum;

};

#endif // RACESERVICEINFO_H
