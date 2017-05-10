#ifndef TEXTLABEL_H
#define TEXTLABEL_H

#include "GlobDef.h"
#include <QLabel>
#include <QString>

class TextLabel : public QLabel
{
    Q_OBJECT
    Q_PROPERTY(QString game_status READ game_getStatus WRITE game_setStatus)

public:
    QString game_getStatus() const;
    void game_setStatus(QString mode);

private:
    QString game_status;

public:
    explicit TextLabel(QWidget *parent = 0);

    void game_setMode(Mode mode);
    void game_setErrorMode(bool isError);
    void game_setTextUnderline(const QString& text, int beg, int end);
public slots:
    void game_setFontName(const QString& fontName);
    void game_setFontSize(int fontSize);

private:
    Mode    m_mode;
    bool    m_isError;
    QString m_fontName;
    int     m_fontSize;
    QString m_text;
    int     m_beg;
    int     m_end;

    void game_refreshStyleSheet();
    void game_refreshText();
};

#endif // TEXTLABEL_H
