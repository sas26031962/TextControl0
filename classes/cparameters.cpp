#include "cparameters.h"

cParameters::cParameters(
    QLineEdit *line_edit_parameter,
    QComboBox *combo_box_parameter,
    QComboBox *combo_box_categories,
    QObject *parent
    ) : QObject(parent)
{
    qleParameterIncoming = line_edit_parameter;
    qcbParameter = combo_box_parameter;
    qcbCategories = combo_box_categories;

    connect(qcbParameter, SIGNAL(currentIndexChanged(int)), this, SLOT(execComboBoxCurrentIndexChanged(int)));
}

cParameters::~cParameters()
{

}

void cParameters::loadItemsFromFile()
{
    qslParameters = cLoadFiles::loadStringListFromFile(cLoadFiles::qsProgramPath + qsParametersFileName);
    qcbParameter->clear();
    qcbParameter->addItems(qslParameters);
}

void cParameters::execComboBoxCurrentIndexChanged(int x)
{
    QString s = qcbParameter->itemText(x);
    qDebug() << "ComboBoxParameterIndexChanged:" << x << " Text=" << s;
    qleParameterIncoming->setText(s);
}

void cParameters::execActionAppendToParameterList()
{
    QString info = "Parameters > Append to Parameter list:";
    //---
    //+Формирование строки с индексом в формате '#'<index><string>
    QString s = "";
    int i = qcbCategories->currentIndex();
    qDebug() << "Current index of Categories=" << i;

    if(i > 0)
    {
        s += '#';
        s += QString::number(i);
    }
    s += qleParameterIncoming->text();
    qleParameterIncoming->setText(s);
    //+
    if(s.length() > 0)
    {
        if(qslParameters.contains(s))
        {
            info += s;
            info += " exist in this list, nothing to do!";
        }
        else
        {
            qslParameters.append(s);
            //Запись списка параметров в файл
            QString qsFileName = cLoadFiles::qsProgramPath + qsParametersFileName;
            bool x = cLoadFiles::saveStringListToFile(qsFileName, qslParameters);
            qcbParameter->addItem(s);
            info += s;
            info += ", strings count=";
            info += QString::number(qcbParameter->count());
            if(x)
            {
                info += " stored to file:";
                info += qsFileName;
            }
        }
    }
    else
    {
        info += " empty string, nothing to do";
    }

    //---
    emit setStatus(info);
}
