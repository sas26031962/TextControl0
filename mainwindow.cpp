#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include <QStatusBar>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    LoadFiles = new cLoadFiles(ui->textBrowserData);

    connect(this, &MainWindow::setStatus, this, &MainWindow::execSetStatus);
    connect(ui->actionLoadFromFile, &QAction::triggered, this, &MainWindow::execActionLoadFromFile);
    connect(ui->actionRemoveSquareBrackets, &QAction::triggered, this, &MainWindow::execActionRemoveSquareBrackets);

    QString appPath = QCoreApplication::applicationFilePath();
    QFileInfo fileInfo(appPath);

//    qDebug() << "Полный путь:" << appPath;
//    qDebug() << "Директория:" << fileInfo.path();
//    qDebug() << "Имя файла:" << fileInfo.fileName();
//    qDebug() << "Базовое имя (без расширения):" << fileInfo.completeBaseName();
//    qDebug() << "Суффикс (расширение):" << fileInfo.suffix();
//    qDebug() << "Абсолютный путь:" << fileInfo.absoluteFilePath();
//    qDebug() << "Канонический путь:" << fileInfo.canonicalFilePath();

    // Определение конкретной ОС
    #if defined(Q_OS_WIN)
        qDebug() << "Running on Windows";
        IsLinux = false;
        IsWindows = true;
    #elif defined(Q_OS_LINUX)
        qDebug() << "Running on Linux";
        IsLinux = true;
        IsWindows = false;
    #else
        qDebug() << "Running on unknown OS";
    #endif

    QString qsDirectory = fileInfo.path();
    if(IsLinux)
    {
        LoadFiles->qsProgramPath = qsDirectory;
        qsCtorMessage = "Ctor > OS Linux detected";
    }
    else if(IsWindows)
    {
        int x = qsDirectory.lastIndexOf('/');
        LoadFiles->qsProgramPath = qsDirectory.mid(0, x);
        qsCtorMessage = "Ctor > OS Windows detected";
    }
    else
    {
        qsCtorMessage = "Ctor > Unknown OS detected";

    }
    qDebug() << "Path to programm directory:" << LoadFiles->qsProgramPath;

    //=========================================================================
    //---Actions---
    QPushButton * pbLoadFile = new QPushButton("Загрузка");
    pbLoadFile->setCursor(Qt::PointingHandCursor);
    connect(pbLoadFile, static_cast<void(QPushButton::*)()>(&QPushButton::pressed),this, [this](){
        qDebug() << "PushButton 'Load' click";
        execActionLoadFromFile(false);
    });
    ui->statusBar->addWidget(pbLoadFile);
    //---
    QPushButton * pbRemoveBracket = new QPushButton("Скобки удалить");
    pbRemoveBracket->setCursor(Qt::PointingHandCursor);
    connect(pbRemoveBracket, static_cast<void(QPushButton::*)()>(&QPushButton::pressed),this, [this](){
        qDebug() << "PushButton 'Search' click";
        execActionRemoveSquareBrackets(false);
    });
    ui->statusBar->addWidget(pbRemoveBracket);
    //---
    QPushButton * pbSearchParameter = new QPushButton("Поиск");
    pbSearchParameter->setCursor(Qt::PointingHandCursor);
    connect(pbSearchParameter, static_cast<void(QPushButton::*)()>(&QPushButton::pressed),this, [this](){
        qDebug() << "PushButton 'Search' click";
        execActionSearchPattern(false);
    });
    ui->statusBar->addWidget(pbSearchParameter);
    //---
    QPushButton * pbEmbraceSquareBracketOfParameter = new QPushButton("Скобки добавить");
    pbEmbraceSquareBracketOfParameter->setCursor(Qt::PointingHandCursor);
    connect(pbEmbraceSquareBracketOfParameter, static_cast<void(QPushButton::*)()>(&QPushButton::pressed),this, [this](){
        qDebug() << "PushButton 'Embrace' click";
        execActionEmbraceSquareBrackets(false);
    });
    ui->statusBar->addWidget(pbEmbraceSquareBracketOfParameter);
    //---
    QPushButton * pbSwapParameter = new QPushButton("Обмен");
    pbSearchParameter->setCursor(Qt::PointingHandCursor);
    connect(pbSwapParameter, static_cast<void(QPushButton::*)()>(&QPushButton::pressed),this, [this](){
        qDebug() << "PushButton 'Swap' click";
        execActionSwapParts(false);
    });
    ui->statusBar->addWidget(pbSwapParameter);
    //---

    emit setStatus(qsCtorMessage);

}//End of ctor

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::execSetStatus(QString s)
{
    qDebug() << s;
    ui->textBrowserLog->append(s);
}

void MainWindow::execActionLoadFromFile(bool x)
{
    QString info = "execActionLoadFiles() > ";
    QString qsFileName = LoadFiles->qsProgramPath + "/data/Text.txt";
    info += "FileName=";
    info += qsFileName;

    int n = LoadFiles->loadStringsFromFile(qsFileName);
    if(n > 0)
    {
        //Установка курсора на начало текста
        int CursorPlace = 0;
        QString s = LoadFiles->qslListIn.at(CursorPlace);
        if (safeColorLine(ui->textBrowserData, CursorPlace, Qt::blue))
        {
            ui->LineEditSource->setText(s);
            info += " load: ";
            info += QString::number(n);
            info += " lines";
        }
        else
        {
            info += "String ";
            info += QString::number(CursorPlace);
            info += " not exist or error detected\n";
        }
    }
    else
    {
        info += " no strings loaded!!!";
    }
    emit setStatus(info);
}

void MainWindow::execActionRemoveSquareBrackets(bool x)
{
    QString info = "execActionRemoveSquareBrackets() > ";
    QStringList qslListOut;
    qslListOut.clear();
    ui->textBrowserData->clear();

    foreach (auto s, LoadFiles->qslListIn)
    {
        QString sOut = LoadFiles->removeSquareBracket(s);
        qslListOut.append(sOut);
        ui->textBrowserData->append(sOut);
    }

    //Установка курсора на начало текста
    int CursorPlace = 0;
    QString s = LoadFiles->qslListIn.at(CursorPlace);
    if (safeColorLine(ui->textBrowserData, CursorPlace, Qt::blue))
    {
        ui->LineEditSource->setText(s);
        info += " processing: ";
        info += QString::number(qslListOut.count());
        info += " lines\n";
    }
    else
    {
        info += "String ";
        info += QString::number(CursorPlace);
        info += " not exist or error detected\n";
    }

    //Сохранение результата в файл
    QString qsFileName = LoadFiles->qsProgramPath + "/data/TextOut.txt";
    bool result = cLoadFiles::saveStringListToFile(qsFileName, qslListOut);

    info += "Save result ";
    if(result)info += "Ok"; else info += "Failure";
    emit setStatus(info);
}

void MainWindow::execActionEmbraceSquareBrackets(bool x)
{
    QString info = "execActionEmbraceSquareBrackets";
    emit setStatus(info);
}

void MainWindow::execActionSwapParts(bool x)
{
    QString info = "execActionSwapParts\n";
    QString result = swapNameFamily(ui->LineEditParameter->text());
    ui->LineEditParameter->setText(result);
    //info += "Result=";
    //info += result;
    emit setStatus(info);
}

QString MainWindow::swapNameFamily(QString s)
{
    QString s0 = s.simplified();
    qDebug() << "Simplified: " << s0;

    int x = s0.indexOf(' ');

    if(x < 0)
    {
        //Возвращаем строку без изменений
        return s;
    }
    else
    {
        QString qsHead = s.mid(0,x);
        QString qsTail = s.mid(x + 1);
        qDebug() << "Index of SPACE=" << x << " Head=" << qsHead << " Tail=" << qsTail;

        //Возвращаем изменённую строку
        QString qsResult = qsTail + " " + qsHead;
        return qsResult;
    }
}

void MainWindow::execActionSearchPattern(bool x)
{
    QString info = "execActionSearchPattern:";
    //---
    QString qsSource = ui->LineEditSource->text();
    QString qsParameter = ui->LineEditParameter->text();
    QVector<int> * qvOutput = new QVector<int>();
    qvOutput->clear();

    int index = 0;//Индекс первого вхождения подстроки

    QString qsTail = "";

    while(index >= 0)
    {
        if(qvOutput->count() > 0)
        {
            //---
            index = qsTail.indexOf(qsParameter);
            //qDebug() << "X=" << index << " branch 1";

            if(index >= 0)
            {
                qsTail = qsTail.mid(index + qsParameter.length());
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
            index = qsSource.indexOf(qsParameter);
            //qDebug() << "X=" << index << " branch 0";

            if(index >= 0)
            {
                qsTail = qsSource.mid(index + qsParameter.length());
                qvOutput->append(index);

                info += "X=";
                info += QString::number(index);
                info += " branch 0\n";
            }
            else
            {
                qsTail = qsSource;
            }
            //---
        }

        //Вывод информации после текущей итерации
        if(x > 0)
        {
            //qDebug() << "Step:" << qvOutput->count() << " Tail=" << qsTail;
            info += " Step:";
            info += QString::number(qvOutput->count());
            info += " Tail=";
            info += qsTail;
            info += "\n";
        }
    }
    //Вывод информации после последней итерации
    //qDebug() << "End of process, count:" << qvOutput->count();
    info += "End of process, count:";
    info += QString::number(qvOutput->count());
    //---
    emit setStatus(info);
}

bool MainWindow::safeColorLine(QTextBrowser *textBrowser, int lineNumber, const QColor &color)
{
    if (!textBrowser || !textBrowser->document()) {
        return false;
    }

    QTextDocument *doc = textBrowser->document();
    if (lineNumber < 0 || lineNumber >= doc->blockCount()) {
        return false; // Строка не существует
    }

    QTextCursor cursor(doc);
    cursor.movePosition(QTextCursor::Start);

    for (int i = 0; i < lineNumber; ++i) {
        cursor.movePosition(QTextCursor::NextBlock);
    }

    cursor.select(QTextCursor::LineUnderCursor);

    QTextCharFormat format;
    format.setForeground(color);
    cursor.mergeCharFormat(format);

    return true;
}

