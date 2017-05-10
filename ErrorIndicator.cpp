#include "ErrorIndicator.h"

ErrorIndicator::ErrorIndicator(QWidget *parent) :
    QLabel(parent)
{
    game_setStatus("SemaphoreOff");
    setText(tr("rectify an error!"));
}

QString ErrorIndicator::game_getStatus() const
{
    return game_status;
}

void ErrorIndicator::game_setStatus(const QString& status)
{
    game_status = status;
    setStyleSheet(GlobalRes::getQSS());
}
