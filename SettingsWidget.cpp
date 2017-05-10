#include "SettingsWidget.h"
#include <QLayout>
#include <QLabel>
#include <QComboBox>
#include <QPainter>

SettingsWidget::SettingsWidget(QWidget *parent) :
    QWidget(parent)
{
    QLabel* topNameLabel = new QLabel;
    topNameLabel->setStyleSheet(
            "QLabel {"
            "font-family:      tahoma;"
            "font-style:       normal;"
            "font-size:        18px;"
            "color: #444444;"
            "}");
    topNameLabel->setText(tr("Settings"));
    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(topNameLabel);

    QLabel* fontNameLabel = new QLabel;
    fontNameLabel->setText(tr("Font") + ":");
    fontNameComboBox = new QComboBox;
    fontNameComboBox->setDuplicatesEnabled(false);
    fontNameComboBox->addItem("Arial");
    fontNameComboBox->addItem("Courier New");
    fontNameComboBox->addItem("Garamond");
    fontNameComboBox->addItem("Georgia");
    fontNameComboBox->addItem("Arial");
    fontNameComboBox->addItem("Lucida Console");
    fontNameComboBox->addItem("Lucida Sans");
    fontNameComboBox->addItem("Palatino Linotype");
    fontNameComboBox->addItem("Tahoma");
    fontNameComboBox->addItem("Times New Roman");
    fontNameComboBox->addItem("Trebuchet MS");
    fontNameComboBox->addItem("Verdana");
    fontNameComboBox->setCurrentIndex(8);
    fontNameComboBox->setAutoFillBackground(false);
    QHBoxLayout* fontNameLayout = new QHBoxLayout;
    fontNameLayout->addWidget(fontNameLabel);
    fontNameLayout->addWidget(fontNameComboBox);
    mainLayout->addLayout(fontNameLayout);

    QHBoxLayout* fontSizeLayout = new QHBoxLayout;
    QLabel* fontSizeLabel = new QLabel;
    fontSizeLabel->setText(tr("Font size") + ":");

    fontSizeSlider = new QSlider(Qt::Horizontal);
    fontSizeSlider->setRange(12, 25);
    fontSizeSlider->setSingleStep(1);
    fontSizeSlider->setValue(17);

    fontSizeLayout->addWidget(fontSizeLabel);
    fontSizeLayout->addWidget(fontSizeSlider);
    mainLayout->addLayout(fontSizeLayout);

    setStyleSheet(
            ".SettingsWidget {"
            "border-radius:    11px;"
            "background-color: #82d352;"
            "}");

    setLayout(mainLayout);
}

void SettingsWidget::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
