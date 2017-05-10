#ifndef INPUTLINE_H
#define INPUTLINE_H

#include "GlobDef.h"
#include <QLineEdit>
#include <QString>

class InputLine : public QLineEdit
{
    Q_OBJECT
    Q_PROPERTY(QString game_status READ game_getStatus WRITE game_setStatus)

public:
    QString game_getStatus() const;
    void game_setStatus(QString mode);

private:
    QString game_status;

public:
    explicit InputLine(QWidget *parent = 0);

    void game_setMode(Mode mode);
    void game_setErrorMode(bool isError);

public slots:
    void game_setFontName(const QString& fontName);
    void game_setFontSize(int size);

private:    
    Mode    m_mode;
    bool    m_isError;
    QString m_fontName;
    int     m_fontSize;

    void game_refreshStyleSheet();
};

#endif // INPUTLINE_H
