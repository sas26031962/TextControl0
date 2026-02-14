#ifndef CLOADFILES_H
#define CLOADFILES_H

#include <QSettings>
#include <memory>
#include <QStringList>
#include <QFile>
#include <QTextStream>
#include <QRegularExpression>
#include <QTextBrowser>

#include "classes/cimportfiles.h"
#include "classes/cinifile.h"

class cLoadFiles
{
    //Атрибуты
    QTextBrowser * TextBrowser;

public:

    QStringList qslList;

    //Конструкторы
    cLoadFiles(QTextBrowser * TextBrowser);

    //Методы
    void clearLines();
    void appEndItem(QString s);

    static bool saveStringListToFile(const QString& fileName, const QStringList& list);
    static QStringList loadStringListFromFile(const QString& fileName);
    int loadStringsFromFile(const QString& fileName);

};

#endif // CLOADFILES_H
