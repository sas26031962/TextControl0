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

#include "classes/cenvironment.h"

class cLoadFiles
{
    //Атрибуты
    QTextBrowser * TextBrowser;

public:

    QStringList qslListIn;
    QString qsProgramPath;

    //Конструкторы
    cLoadFiles(QTextBrowser * TextBrowser);

    //Методы
    void clearLines();
    void appEndItem(QString s);
    QString removeSquareBracket(QString s);
    QString getFirstLineFromDocument(QTextBrowser *textBrowser);

    static bool saveStringListToFile(const QString& fileName, const QStringList& list);
    static QStringList loadStringListFromFile(const QString& fileName);
    int loadStringsFromFile(const QString& fileName);

};

#endif // CLOADFILES_H
