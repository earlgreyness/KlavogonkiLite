#ifndef GLOBDEF_H
#define GLOBDEF_H

#include <QDebug>
#include <QString>

class QString;

enum Mode
{
    SemaphoreOff,
    SemaphoreRed,
    SemaphoreRedAndYellow,
    SemaphoreGreen,
    Error,
    Finish
};

class GlobalRes
{
public:
    static void init();
    static QString getQSS();
private:

    static QString global_qss;
};

int game_randomInteger(int a, int b);
bool game_isStringsEqual(const QString& what, const QString& pattern);

#endif // GLOBDEF_H
