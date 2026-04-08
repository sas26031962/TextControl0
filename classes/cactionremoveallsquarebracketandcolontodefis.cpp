#include "cactionremoveallsquarebracketandcolontodefis.h"

cActionRemoveAllSquareBracketAndColonToDefis::cActionRemoveAllSquareBracketAndColonToDefis(
        QTextBrowser * text_browser,
        cLoadFiles *load_files,
        QObject *parent
        ) : QObject(parent)
{
    TextBrowser = text_browser;
    LoadFiles = load_files;
}

cActionRemoveAllSquareBracketAndColonToDefis::~cActionRemoveAllSquareBracketAndColonToDefis()
{
    //...
}

void cActionRemoveAllSquareBracketAndColonToDefis::exec()
{
    QString info = "execActionRemoveAllSquareBracketAndColonToDefis() > ";
    QStringList qslListOut;
    qslListOut.clear();
    TextBrowser->clear();

    foreach (auto s, LoadFiles->qslListIn)
    {
        QString sOut = removeSquareBracketAndColonToDefisFromLine(s);
        qslListOut.append(sOut);
        TextBrowser->append(sOut);
    }

    //Сохранение результата в файл
    info += LoadFiles->storeTargetFile(qslListOut);

    emit setStatus(info);
}

QString cActionRemoveAllSquareBracketAndColonToDefis::removeSquareBracketAndColonToDefisFromLine(QString s)
{
    QString qsOut = s;

    qsOut.remove('[');
    qsOut.remove(']');
    qsOut.replace(':', '-');

    return qsOut;
}
