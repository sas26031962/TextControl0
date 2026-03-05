#ifndef CLOADFILES_H
#define CLOADFILES_H

#include <QSettings>
#include <memory>
#include <QStringList>
#include <QFile>
#include <QTextStream>
#include <QRegularExpression>
#include <QTextBrowser>
#include <QDebug>
#include <QTextBlock>

class cLoadFiles
{
    //Атрибуты
    QTextBrowser * TextBrowser;

public:
    static bool IsLinux;
    static bool IsWindows;
    static bool IsUTF8;
    static bool IsWindows1251;

    QStringList qslListIn;
    QString qsProgramPath;

    //Конструкторы
    cLoadFiles(QTextBrowser * TextBrowser);

    //Методы
    void clearLines();
    void appEndItem(QString s);
    QString getFirstLineFromDocument(QTextBrowser *textBrowser);

    static bool saveStringListToFile(const QString& fileName, const QStringList& list);
    static QStringList loadStringListFromFile(const QString& fileName);
    int loadStringsFromFile(const QString& fileName);

};

#endif // CLOADFILES_H
