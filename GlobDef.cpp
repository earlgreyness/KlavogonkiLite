#include "GlobDef.h"
#include <QString>
#include <QFile>
#include <QTextStream>

int game_randomInteger(int a, int b)
{
    return qrand() % (b - a + 1) + a;
}


void GlobalRes::init()
{
    QString fileName = "qss.qss";
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "main() : can't open file : " << fileName;
        return;
    }
    else
    {
        QTextStream stream(&file);
        global_qss = stream.readAll();
    }
    file.close();
    qDebug() << global_qss;
}

QString GlobalRes::getQSS()
{
    return global_qss;
}


bool game_isStringsEqual(const QString& what, const QString& pattern)
{
    if (what.size() != pattern.size())
    {
        return false;
    }
    int size = pattern.size();
    for (int i = 0; i < size; ++i)
    {
        if (what[i] == pattern[i])
        {
            continue;
        }
        if (pattern[i].unicode() == 8212 && what[i] == '-')
        {
            continue;
        }
        if (pattern[i].unicode() == 8211 && what[i] == '-')
        {
            continue;
        }
        if (pattern[i].unicode() == 8210 && what[i] == '-')
        {
            continue;
        }
        if (pattern[i].unicode() == 171 && what[i] == '"')
        {
            continue;
        }
        if (pattern[i].unicode() == 187 && what[i] == '"')
        {
            continue;
        }
        if (pattern[i].unicode() == 1105 && what[i] == 'å')
        {
            continue;
        }
        if (pattern[i].unicode() == 1025 && what[i] == 'Å')
        {
            continue;
        }
        return false;
        //QChar chLow = '¸';//1105
        //QChar chBig = '¨';//1025
        //qDebug() << chLow << ":" << chLow.unicode() << chBig << ":" << chBig.unicode();
    }
    return true;
}
