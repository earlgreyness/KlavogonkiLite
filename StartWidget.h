#ifndef STARTWIDGET_H
#define STARTWIDGET_H

#include <QWidget>
#include "GlobDef.h"
#include "SettingsWidget.h"

class QRadioButton;
class QLabel;
class QPushButton;

class StartWidget : public QWidget
{
    Q_OBJECT
public:
    explicit StartWidget(QWidget *parent = 0);

signals:
    void startGameButtonClicked();

public slots:

private:
    QRadioButton* radioButton1;
    QRadioButton* radioButton2;
    QRadioButton* radioButton3;
    QLabel*       label1;
    QLabel*       label2;
    QLabel*       label3;
    QLabel*       labelSecond1;
    QLabel*       labelSecond2;
    QLabel*       labelSecond3;

    SettingsWidget* settingsWidget;

    QPushButton*  startGameButton;

};

#endif // STARTWIDGET_H
