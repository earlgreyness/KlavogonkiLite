#ifndef SETTINGSWIDGET_H
#define SETTINGSWIDGET_H

#include <QWidget>
#include "GlobDef.h"
class QLabel;
class QComboBox;
class QSlider;

class SettingsWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SettingsWidget(QWidget *parent = 0);
protected:
    void paintEvent(QPaintEvent *);
private:
    //QLabel* topNameLabel;
public:

    QComboBox* fontNameComboBox;
    QSlider*   fontSizeSlider;
    //QSlider*   speedSlider;

};

#endif // SETTINGSWIDGET_H
