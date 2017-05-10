#ifndef DELIMETER_H
#define DELIMETER_H

#include <QWidget>

class Delimeter : public QWidget
{
    Q_OBJECT
public:
    explicit Delimeter(QWidget *parent = 0);

protected:
    void paintEvent(QPaintEvent* event);

signals:

public slots:

};

#endif // DELIMETER_H
