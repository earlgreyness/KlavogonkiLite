#ifndef ERRORINDICATOR_H
#define ERRORINDICATOR_H

#include "GlobDef.h"
#include <QLabel>
#include <QString>

class ErrorIndicator : public QLabel
{
    Q_OBJECT
    Q_PROPERTY(QString game_status READ game_getStatus WRITE game_setStatus)

public:
    explicit ErrorIndicator(QWidget *parent = 0);

    QString game_getStatus() const;
    void game_setStatus(const QString& mode);

private:
    QString game_status;
};

#endif // ERRORINDICATOR_H
