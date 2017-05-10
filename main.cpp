#include "Smart.h"
#include <QApplication>
#include <QTextCodec>
#include <QTime>
#include <QTranslator>
#include "GlobDef.h"

QString GlobalRes::global_qss;
int main(int argc, char** argv)
{
    QApplication app(argc, argv);


    QTranslator* translator(new QTranslator(&app));
    translator->load(":/ru.qm");
    app.installTranslator(translator);
//    QTextCodec::setCodecForTr(QTextCodec::codecForName("CP1251"));
//    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("CP1251")); //"UTF8"
    qsrand(QTime(0, 0, 0, 0).secsTo(QTime::currentTime()));

    GlobalRes::init();

    Game* game = new Game;
    return app.exec();
}
