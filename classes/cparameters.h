#ifndef CPARAMETERS_H
#define CPARAMETERS_H

#include <QObject>
#include <QString>
#include <QStringList>
#include <QComboBox>
#include <QLineEdit>
#include <QDebug>

#include "classes/cloadfiles.h"

class cParameters : public QObject
{
    Q_OBJECT
public:
    //Аргументы
    QString qsParametersFileName = "/data/Parameters.txt";
    QStringList qslParameters;

    QComboBox * qcbParameter;
    QComboBox * qcbCategories;
    QLineEdit * qleParameterIncoming;

    //Конструкторы
    explicit cParameters(
        QLineEdit * line_edit_parameter,
            QComboBox * combo_box_parameter,
            QComboBox * combo_box_categories,
        QObject *parent = 0
        );
    ~cParameters();

    //Методы
    void loadItemsFromFile();

signals:
    void setStatus(QString s);

public slots:
    void execComboBoxCurrentIndexChanged(int x);
    void execActionAppendToParameterList();
};

#endif // CPARAMETERS_H
