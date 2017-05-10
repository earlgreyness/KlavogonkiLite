#ifndef CHAMFEREDWIDGET_H
#define CHAMFEREDWIDGET_H

#include <QWidget>
#include "GlobDef.h"


class QVBoxLayout;
class TextLabel;
class ErrorIndicator;
class InputLine;
class Delimeter;


class ChamferedWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ChamferedWidget(QWidget *parent = 0);

    void game_setMode(Mode mode);
    void game_setErrorMode(bool isError);

    void game_inputLineClear();
    void game_textLabelSetTextUnderline(const QString& text, int beg, int end);

public slots:
    void game_inputLineSetTextSize(int size);
    void game_textLabelSetTextSize(int size);
    void game_setTextName(const QString& fontName);

protected:
    void paintEvent(QPaintEvent*);

signals:
    void game_inputLineTextEdited(QString);

private:
    Mode m_mode;
    bool m_isError;

    QVBoxLayout*    m_layout1;
    QVBoxLayout*    m_layout2;

    TextLabel*      m_textLabel;
    ErrorIndicator* m_errorIndicator;
    InputLine*      m_inputLine;
};

#endif // CHAMFEREDWIDGET_H
