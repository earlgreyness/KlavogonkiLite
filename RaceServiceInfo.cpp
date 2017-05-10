#include "RaceServiceInfo.h"
#include <QFile>
#include <QTextStream>
#include <QTimer>

RaceServiceInfo::RaceServiceInfo(QObject *parent)
    : QObject(parent)
    , m_time(0, 0, 0, 0)
    , m_timeLeft(10000)
    , m_flag(false)
    , lastTimePressed()
{
    m_timer = new QTimer(this);
    m_curStringNum = 0;
    m_beg = 0;
    m_end = 0;
    m_isError = false;
    m_numErrors = 0;

    mspeed = 0;
    mspeedArrow = 0;
    lastLength = 0;
    pressedNum = 0;
    lastPressedNum = 0;
}

void RaceServiceInfo::resetAll()
{
    //m_strings.clear();
    //m_recentNumbers.clear();
    m_curStringNum = 0;
    mspeed = 0;
    mspeedArrow = 0;
    m_beg = 0;
    m_end = 0;
    m_isError = false;
    m_numErrors = 0;
}

void RaceServiceInfo::game_selectRandomString() // перебираем все строки без повторений в случайном порядке
{
    if (m_strings.size() == 0)
    {
        qDebug() << "RaceServiceInfo : game_selectRandomString() : m_strings.size() == 0";
        m_strings.push_back("Hello, world!");
    }
    if (m_recentNumbers.size() == m_strings.size())
    {
        m_recentNumbers.clear();
        if (m_strings.size() != 1)
        {
            m_recentNumbers.push_back(m_curStringNum);
        }
    }
    int newNumber = game_randomInteger(0, m_strings.size() - 1);
    QVector<int>::iterator it = qFind(m_recentNumbers.begin(), m_recentNumbers.end(), newNumber);
    while (it != m_recentNumbers.end())
    {
        newNumber = game_randomInteger(0, m_strings.size() - 1);
        it = qFind(m_recentNumbers.begin(), m_recentNumbers.end(), newNumber);
    }
    m_curStringNum = newNumber;
    m_recentNumbers.push_back(m_curStringNum);
}

void RaceServiceInfo::game_initStringsFromFile(const QString& fileName)
{
    m_strings.clear();
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "RaceServiceInfo : game_initStringsFromFile : can't open file : " << fileName;
    }
    else
    {
        QTextStream stream(&file);
        QString line;
        while (!stream.atEnd())
        {
            line = stream.readLine();
            if (!line.isEmpty())
            {
                m_strings.push_back(line);
            }
        }
    }
    if (m_strings.isEmpty())
    {
        qDebug() << "RaceServiceInfo : game_initStringsFromFile : m_info->m_strings is empty!";
        m_strings.push_back("Hello, world!");
    }
}

void RaceServiceInfo::game_selectNextWord()
{
    while (m_strings[m_curStringNum][m_end] == ' ')
    {
        ++m_end;
    }
    m_beg = m_end;
    while (m_strings[m_curStringNum][m_end] != ' ' && m_end < m_strings[m_curStringNum].size())
    {
        ++m_end;
    }
    if (m_end < m_strings[m_curStringNum].size())
    {
        ++m_end;
    }
}
