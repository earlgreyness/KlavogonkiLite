#ifndef TIMEWIDGET_H
#define TIMEWIDGET_H

#include <QLabel>
#include "GlobDef.h"
#include <QString>

class TimeWidget : public QLabel
{
    Q_OBJECT
public:
    explicit TimeWidget(QWidget *parent = 0);

    void game_setMode(Mode mode);
    void game_setDark(bool isDark);

/*protected:
    void paintEvent(QPaintEvent* event);*/

signals:

public slots:
    void game_setTime(int msecs);
    void game_setTimeout(int secs);

private:
    Mode    m_mode;
    bool    m_dark;
    QString m_time;
    int     m_timeout;

    void game_refreshText();

};

#endif // TIMEWIDGET_H
