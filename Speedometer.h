#ifndef SPEEDOMETER_H
#define SPEEDOMETER_H

#include "GlobDef.h"
#include <QWidget>
#include <QPixmap>

class Speedometer : public QWidget
{
    Q_OBJECT

public:
    explicit Speedometer(QWidget *parent = 0);

    void game_setMode(Mode mode);
    void game_setDark(bool isDark);

public slots:
    void game_setLabelSpeed(double speed);
    void game_setArrowSpeed(double speed);
    void game_setNumErrors(int numErrors);

protected:
    void paintEvent(QPaintEvent* event);

private:
    Mode    m_mode;
    bool    m_dark;
    double  m_labelSpeed;
    double  m_arrowSpeed;
    int     m_numErrors;
    QPixmap pixmapPanel;
    QPixmap pixmapArrow;
    QPixmap pixmapPanelTop;
    QPixmap pixmapDarkBackground;

    double game_angle(double speed);
};

#endif // SPEEDOMETER_H
