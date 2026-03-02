#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStringList>
#include <QDebug>
#include <QFileInfo>
#include <QTextDocument>
#include <QTextBrowser>
#include <QTextCursor>
#include <QTextCharFormat>

#include "classes/cloadfiles.h"
#include "classes/stvarmem.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

//    bool IsLinux = false;
//    bool IsWindows = false;
    QString qsCtorMessage;

    varMem<int> vmCurrentListIndex;
    int ListCount = 0;

public:
    //Конструкторы
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    //Методы
    bool setCursorPlace();

private:
    //Атрибуты
    Ui::MainWindow *ui;

cLoadFiles * LoadFiles;
QString qsLine0 = "Винтеркей Серж, Шумилин Артем - Ревизор 21 - Ревизор: возвращение в СССР 21 [Сергей Уделов, 2024, Попаданцы, 64 kbps]";

//Методы
QString swapNameFamily(QString s);
bool safeColorLine(QTextBrowser *textBrowser, int lineNumber, const QColor &color);


private slots:
void execSetStatus(QString s);
void execActionLoadFromFile(bool x);
void execActionRemoveSquareBrackets(bool x);
void execActionEmbraceSquareBrackets(bool x);
void execActionSearchPattern(bool x);
void execActionSwapParts(bool x);
void execActionSelectNextString(bool x);
void execActionSelectPreviousString(bool x);

signals:
void setStatus(QString s);


};

#endif // MAINWINDOW_H
