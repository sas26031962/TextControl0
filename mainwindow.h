#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStringList>
#include <QDebug>

#include "classes/cloadfiles.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

cLoadFiles * LoadFiles;
//QStringList * qslLines;

private slots:
void execSetStatus(QString s);
void execActionLoadFromFile(bool x);
void execActionRemoveSquareBrackets(bool x);

signals:
void setStatus(QString s);


};

#endif // MAINWINDOW_H
