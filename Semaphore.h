#ifndef SEMAPHORE_H
#define SEMAPHORE_H

#include "GlobDef.h"
#include <QWidget>
#include <QPixmap>
class QPaintEvent;

class Semaphore : public QWidget
{
    Q_OBJECT
public:
    explicit Semaphore(QWidget *parent = 0);

    void game_setMode(Mode mode);
    void game_setDark(bool isDark);

protected:
    void paintEvent(QPaintEvent* event);

private:
    Mode m_mode;
    bool m_dark;
    QPixmap pixmapOff;
    QPixmap pixmapRed;
    QPixmap pixmapRedAndYellow;
    QPixmap pixmapGreen;
    QPixmap pixmapDarkBackground;
};

#endif // SEMAPHORE_H
