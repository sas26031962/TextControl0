#ifndef CACTIONPROCESSSTRING_H
#define CACTIONPROCESSSTRING_H

#include <QObject>
#include <QString>
#include <QVector>
#include <QLineEdit>
#include <QDebug>

#include "classes/cloadfiles.h"
#include "classes/cparameters.h"

class cActionProcessString : public QObject
{
    Q_OBJECT

    cLoadFiles * LoadFiles;
    cParameters * ParametersInstance;
    QLineEdit * LineEditSource;

public:
    explicit cActionProcessString(
        cLoadFiles * load_files,
        cParameters * parameters,
        QLineEdit * line_edit_source,
        QObject *parent = 0
        );

    ~cActionProcessString();

signals:
    void setStatus(QString s);

public slots:
    void exec(int index);

};

#endif // CACTIONPROCESSSTRING_H
