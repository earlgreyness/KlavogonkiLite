#include "StartWidget.h"
#include <QLayout>
#include <QRadioButton>
#include <QLabel>
#include <QPushButton>

StartWidget::StartWidget(QWidget *parent) :
    QWidget(parent)
{
    QGridLayout* gridLayout = new QGridLayout;

    radioButton1 = new QRadioButton;
    radioButton2 = new QRadioButton;
    radioButton3 = new QRadioButton;
    label1 = new QLabel;
    label2 = new QLabel;
    label3 = new QLabel;
    labelSecond1 = new QLabel;
    labelSecond2 = new QLabel;
    labelSecond3 = new QLabel;

    label1->setText("<font size=\"5\" face=\"tahoma\">" + tr("Customary") + "</font>");
    label2->setText("<font size=\"5\" color=#4692aa face=\"tahoma\">" + tr("Faultless") + "</font>");
    label3->setText("<font size=\"5\" color=#ea6368 face=\"tahoma\">" + tr("Marathon") + "</font>");



    labelSecond1->setText("<font size=\"4\" face=\"tahoma\">" + tr("Customary description") + "</font>");
    labelSecond2->setText("<font size=\"4\" face=\"tahoma\">" + tr("Faultless description") + "</font>");
    labelSecond3->setText("<font size=\"4\" face=\"tahoma\">" + tr("Marathon description") + "</font>");
    labelSecond1->setWordWrap(true);
    labelSecond2->setWordWrap(true);
    labelSecond3->setWordWrap(true);

    labelSecond1->setMinimumWidth(500);

    gridLayout->addWidget(radioButton1, 0, 0);
    gridLayout->addWidget(radioButton2, 2, 0);
    gridLayout->addWidget(radioButton3, 4, 0);
    gridLayout->addWidget(label1, 0, 1);
    gridLayout->addWidget(label2, 2, 1);
    gridLayout->addWidget(label3, 4, 1);
    gridLayout->addWidget(labelSecond1, 1, 1);
    gridLayout->addWidget(labelSecond2, 3, 1);
    gridLayout->addWidget(labelSecond3, 5, 1);

    settingsWidget = new SettingsWidget;

    QHBoxLayout* hLayout = new QHBoxLayout;
    hLayout->addLayout(gridLayout);
    hLayout->addWidget(settingsWidget);

    startGameButton = new QPushButton;
    startGameButton->setText(tr("Play"));
    startGameButton->setMaximumSize(100, 30);
    startGameButton->setMinimumSize(100, 30);

    QVBoxLayout* vLayout = new QVBoxLayout;
    vLayout->addLayout(hLayout);
    vLayout->addWidget(startGameButton);

    radioButton1->setChecked(true);

    connect(startGameButton, SIGNAL(clicked()), this, SIGNAL(startGameButtonClicked()));

    setLayout(vLayout);
}
