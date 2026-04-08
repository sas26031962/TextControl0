#ifndef CACTIONREMOVEALLSQUAREBRACKETANDCOLONTODEFIS_H
#define CACTIONREMOVEALLSQUAREBRACKETANDCOLONTODEFIS_H

#include <QObject>
#include <QString>
#include <QDebug>
#include <QTextBrowser>

#include "classes/cloadfiles.h"

class cActionRemoveAllSquareBracketAndColonToDefis : public QObject
{
    Q_OBJECT

    //Атрибуты
    QTextBrowser * TextBrowser;
    cLoadFiles * LoadFiles;

    //Методы
    QString removeSquareBracketAndColonToDefisFromLine(QString s);

public:
    //Конструкторы и деструкторы
    explicit cActionRemoveAllSquareBracketAndColonToDefis(
            QTextBrowser * text_browser,
            cLoadFiles * load_files,
            QObject *parent = 0
            );

    ~cActionRemoveAllSquareBracketAndColonToDefis();

signals:
    void setStatus(QString s);

public slots:
    void exec();
};

#endif // CACTIONREMOVEALLSQUAREBRACKETANDCOLONTODEFIS_H
