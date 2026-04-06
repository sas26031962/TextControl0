#ifndef CACTIONEMBRACESQUAREBRACKETS_H
#define CACTIONEMBRACESQUAREBRACKETS_H

#include <QObject>
#include <QString>
#include <QLineEdit>

#include "classes/cparameters.h"

class cActionEmbraceSquareBrackets : public QObject
{
    Q_OBJECT

    cParameters * ParametersInstance;
    QLineEdit * qleSource;
public:
    explicit cActionEmbraceSquareBrackets(
        cParameters * parameters,
        QLineEdit * line_edit_source,
        QObject *parent = 0
        );
    ~cActionEmbraceSquareBrackets();

signals:
    void setStatus(QString s);

public slots:
    void exec();
};

#endif // CACTIONEMBRACESQUAREBRACKETS_H
