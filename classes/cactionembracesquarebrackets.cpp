#include "cactionembracesquarebrackets.h"

cActionEmbraceSquareBrackets::cActionEmbraceSquareBrackets(
        cParameters *parameters,
        QLineEdit *line_edit_source,
        QObject *parent
        ) : QObject(parent)
{
    ParametersInstance = parameters;
    qleSource = line_edit_source;
}

cActionEmbraceSquareBrackets::~cActionEmbraceSquareBrackets()
{
    //...
}

void cActionEmbraceSquareBrackets::exec()
{
    QString info = "execActionEmbraceSquareBrackets";
    //---
    QString qsSource = qleSource->text();//ui->LineEditSource;
    QString qsParameter = ParametersInstance->qleParameterIncoming->text();
    if(qsParameter.count() > 0)
    {
        QVector<int> * qvOutput = new QVector<int>();
        qvOutput->clear();

        int x = 0;//Индекс первого вхождения подстроки

        QString qsTail = "";
        QString qsResult = "";

        while(x >= 0)
        {
            if(qvOutput->count() > 0)
            {
                //--- Повторные вхождения
                x = qsTail.indexOf(qsParameter);
                qDebug() << "X=" << x << " branch 1";
                if(x >= 0)
                {
                    qsResult += qsTail.mid(0, x);
                    qsResult += "[[";
                    qsResult += qsParameter;
                    qsResult += "]]";

                    qsTail = qsTail.mid(x + qsParameter.length());
                    qvOutput->append(x);
                }
                //---
            }
            else
            {
                //--- Первое вхождение
                x = qsSource.indexOf(qsParameter);
                qDebug() << "X=" << x << " branch 0";
                if(x >= 0)
                {
                    qsResult = qsSource.mid(0, x);
                    qsResult += "[[";
                    qsResult += qsParameter;
                    qsResult += "]]";
                    qsTail = qsSource.mid(x + qsParameter.length());
                    qvOutput->append(x);
                }
                else
                {
                    qsTail = qsSource;
                }
                //---
            }
        }//End of while(x >= 0)

        qsResult += qsTail;

        qleSource->setText(qsResult);

        qDebug() << "End of process, count:" << qvOutput->count();

    }//End of if(qsParameter.count() > 0)
    else
    {
        info += " > Empty parameter: nothing to do";
    }
    //---
    emit setStatus(info);
}
