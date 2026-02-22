#include "cloadfiles.h"

cLoadFiles::cLoadFiles(QTextBrowser *text_browser)
{
    TextBrowser = text_browser;
}

//=============================================================================

void cLoadFiles::appEndItem(QString s)
{
    TextBrowser->append(s);
}

//=============================================================================
void cLoadFiles::clearLines()
{
    TextBrowser->clear();
}

//=============================================================================
int cLoadFiles::loadStringsFromFile(const QString& fileName)
{
    qslListIn.clear();
    qslListIn = cLoadFiles::loadStringListFromFile(fileName);
    foreach (auto s, qslListIn)
    {
        TextBrowser->append(s);
    }
    return qslListIn.count();
}

QString cLoadFiles::getFirstLineFromDocument(QTextBrowser *textBrowser) {
    QTextDocument *doc = textBrowser->document();
    if (!doc) return QString();

    QTextBlock firstBlock = doc->begin();
    if (firstBlock.isValid()) {
        return firstBlock.text();
    }
    return QString();
}

//=============================================================================

bool cLoadFiles::saveStringListToFile(const QString& fileName, const QStringList& list)
{
    QFile file(fileName);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        return false;
    }
    else
    {
        // Установка кодировки
        QTextStream out(&file);
        if(cEnvironment::iSystemType == WINDOWS_SYSTEM_TYPE)
            out.setCodec("Windows-1251");
        else
            out.setCodec("UTF-8");

        for (const QString& str : list) {
            out << str << "\n";
        }

        file.close();
        return true;
    }
}

//=============================================================================

QStringList cLoadFiles::loadStringListFromFile(const QString& fileName)
{
    QStringList list;
    QFile file(fileName);

    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        in.setCodec("UTF-8");

        while (!in.atEnd()) {
            list << in.readLine();
        }

        file.close();
    }
    return list;
}

//=============================================================================


QString cLoadFiles::removeSquareBracket(QString s)
{
    QString qsOut = "";
    int ColonIndex = s.indexOf(':');
    int LeftBracketIndex = s.indexOf('[');
    int RightBracketIndex = s.indexOf(']');
    QString Acc = "";
    if(ColonIndex > 0)
    {
        Acc = s.mid(0,ColonIndex);
        Acc.append(" -");
        qDebug() << "Head=" << Acc;
        qsOut += Acc;

        Acc = s.mid(ColonIndex + 1, (LeftBracketIndex - ColonIndex - 1));
        qDebug() << "Neck=" << Acc;
        qsOut += Acc;

        Acc = s.mid(LeftBracketIndex + 1, (RightBracketIndex - LeftBracketIndex - 1));
        qDebug() << "Middle=" << Acc;
        qsOut += Acc;

        Acc = s.mid(RightBracketIndex + 1);
        qDebug() << "Taille=" << Acc;
        qsOut += Acc;
    }
    else
    {
        Acc = s.mid(0,LeftBracketIndex);
        qDebug() << "Head=" << Acc;
        qsOut += Acc;

        Acc = s.mid(LeftBracketIndex + 1, (RightBracketIndex - LeftBracketIndex - 1));
        qDebug() << "Middle=" << Acc;
        qsOut += Acc;

        Acc = s.mid(RightBracketIndex + 1);
        qDebug() << "Taille=" << Acc;
        qsOut += Acc;
    }
    return qsOut;
}

//=============================================================================

