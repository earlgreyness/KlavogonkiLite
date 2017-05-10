#ifndef FINISHTRACK_H
#define FINISHTRACK_H

#include "GlobDef.h"
#include <QWidget>
class QLabel;

class TimeResult
{
public:
    QString mins;
    QString secs;
    QString dsecs;

    TimeResult() : mins("00"), secs("00"), dsecs("0") { }
};

class Results
{
public:
    TimeResult time;
    QString speed;
    QString errors;
    QString errorsPercent;

    Results() : time(), speed("0"), errors("0"), errorsPercent("0,00") { }
};

class FinishTrack : public QWidget
{
    Q_OBJECT

public:
    explicit FinishTrack(QWidget *parent = 0);

protected:
    void paintEvent(QPaintEvent* event);
public:
    void game_setMode(Mode mode);
    void game_setDark(bool dark);
private:
    Mode m_mode;
    bool m_dark;

public:
    void game_setResults(int numSymbols, int msecs, int numErrors);
public slots:
    void game_setCarPosition(double percent);

private:
    Results  result;
    QLabel*  label1;
    QLabel*  label2;
    QLabel*  label3;
    QString  pattern;

    double   m_carPosition;

    QPixmap  pixmap;
    QPixmap  pixmapBlack;
    QPixmap  car;

    TimeResult game_getTimeResult(int msecs);
    QString    game_getSpeedResult(int numSymbols, int msecs);
    QString    game_getErrorsPercentResult(int numSymbols, int numErrors);
};

#endif // FINISHTRACK_H
