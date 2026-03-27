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
#include <QSettings>
#include <QMessageBox>
#include <QApplication>
#include <QClipboard>
#include <QTextLayout>
#include <QLineEdit>

#include "classes/cloadfiles.h"
#include "classes/stvarmem.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    QString qsCtorMessage;

    varMem<int> vmCurrentListIndex;
    int ListCount = 0;

    QString qsParametersFileName = "/data/Parameters.txt";
    QString qsIniFilePath = "/settings.ini";
    QStringList qslParameters;
    QStringList qslCategories;

public:
    //Конструкторы
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    //Методы
    bool setCursorPlace();
    QString removeSquareBracketAndColonToDefis(QString s);

protected:
    void closeEvent(QCloseEvent * event);
    bool eventFilter(QObject *obj, QEvent *event) override;

private:
    //Атрибуты
    Ui::MainWindow *ui;

cLoadFiles * LoadFiles;
QString qsLine0 = "Винтеркей Серж, Шумилин Артем - Ревизор 21 - Ревизор: возвращение в СССР 21 [Сергей Уделов, 2024, Попаданцы, 64 kbps]";

//Методы
QString swapNameFamily(QString s);
bool safeColorLine(QTextBrowser *textBrowser, int lineNumber, const QColor &color);
void setLineEditTextFormat(QLineEdit *lineEdit, const QList<QTextLayout::FormatRange> &formats);


private slots:
void execSetStatus(QString s);
void execActionLoadFromFile(bool x);
void execActionRemoveSquareBrackets(bool x);
void execActionEmbraceSquareBrackets(bool x);
void execActionSearchPattern(bool x);
void execActionSwapParts(bool x);
void execActionSelectNextString(bool x);
void execActionSelectPreviousString(bool x);
void execActionStoreString(bool x);
void execActionAppendToList(bool x);
void execActionSeparateStrings(bool x);
void execActionProcessString(bool x);
void execActionRevert(bool x);
void execActionAppendToParameterList();
void execActionCtrlV();

signals:
void setStatus(QString s);


};

#endif // MAINWINDOW_H
