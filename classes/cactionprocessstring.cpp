#include "cactionprocessstring.h"

cActionProcessString::cActionProcessString(
        cLoadFiles *load_files,
        cParameters *parameters,
        QLineEdit *line_edit_source,
        QObject *parent
        ) : QObject(parent)
{
    LoadFiles = load_files;
    ParametersInstance = parameters;
    LineEditSource = line_edit_source;
}

cActionProcessString::~cActionProcessString()
{

}

void cActionProcessString::exec(int index)
{
    //Поиск параметра в строке
    QString qsSource = LoadFiles->qslListIn.at(index);//vmCurrentListIndex.Current
    qDebug() << "Source:" << qsSource;
    QVector<int> * qvOutput = new QVector<int>();
    QString info = "execActionProcessString:\n";
    //---
    foreach (QString qsParameter, ParametersInstance->qslParameters)
    {
        //qDebug() << "->Parameter:" << qsParameter;
        //+
        QString string = "";
        if(qsParameter[0] == '#')
        {
            string = qsParameter.mid(2);
        }
        else
        {
            string = qsParameter;
        }
        //+
        qvOutput->clear();

        int index = 0;//Индекс первого вхождения подстроки

        QString qsTail = "";

        while(index >= 0)
        {
            if(qvOutput->count() > 0)
            {
                //---
                index = qsTail.indexOf(string);//+

                if(index >= 0)
                {
                    //---20260312
                    qsTail.insert(index, '[');
                    qsTail.insert(index + 1, '[');
                    qsTail.insert(index + string.length() + 2, ']');
                    qsTail.insert(index + string.length() + 3, ']');
                    qDebug() << "Branch1: Tail=" << qsTail;
                    //---
                    qsTail = qsTail.mid(index + string.length() + 4);//new
                    qvOutput->append(index);

                    info += "X=";
                    info += QString::number(index);
                    info += " branch 1\n";
                }
                //---
            }
            else
            {
                //---
                index = qsSource.indexOf(string);

                if(index >= 0)
                {
                    //---20260312
                    qsSource.insert(index, '[');
                    qsSource.insert(index + 1, '[');
                    qsSource.insert(index + string.length() + 2, ']');
                    qsSource.insert(index + string.length() + 3, ']');
                    LineEditSource->setText(qsSource);
                    //---
                    qsTail = qsSource.mid(index + string.length() + 4);//new
                    qvOutput->append(index);

                    info += "X=";
                    info += QString::number(index);
                    info += " branch 0\n";
                }
                else
                {
                    qsTail = qsSource;

                    break;
                }
                //---
            }

            //Вывод информации после текущей итерации
            if(index >= 0)
            {
                info += "Parameter=";
                info += string;
                info += "\n";
            }
        }//End of while(index >= 0)

    }
    //---

    emit setStatus(info);
}
