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
    //Конструкторы
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    //Методы
    //QString removeSquareBracket(QString s);

private:
    //Атрибуты
    Ui::MainWindow *ui;

cLoadFiles * LoadFiles;
QString qsLine0 = "Винтеркей Серж, Шумилин Артем - Ревизор 21 - Ревизор: возвращение в СССР 21 [Сергей Уделов, 2024, Попаданцы, 64 kbps]";

private slots:
void execSetStatus(QString s);
void execActionLoadFromFile(bool x);
void execActionRemoveSquareBrackets(bool x);

signals:
void setStatus(QString s);


};

#endif // MAINWINDOW_H
