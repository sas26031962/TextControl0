#include "mainwindow.h"
#include "ui_mainwindow.h"

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

    QString qsDirectory = fileInfo.path();
    int iLastSlashPosition = qsDirectory.lastIndexOf('/');
    LoadFiles->qsProgramPath = qsDirectory.mid(0, iLastSlashPosition);

    qDebug() << "Path to programm directory:" << LoadFiles->qsProgramPath;

}

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
    QString qsFileName = LoadFiles->qsProgramPath + "/data/Text.txt";
    int n = LoadFiles->loadStringsFromFile(qsFileName);
    emit setStatus("execActionLoadFiles() > load: " + QString::number(n) + " lines");
}

void MainWindow::execActionRemoveSquareBrackets(bool x)
{
    QStringList qslListOut;
    qslListOut.clear();

    foreach (auto s, LoadFiles->qslListIn)
    {
        QString sOut = LoadFiles->removeSquareBracket(s);
        qslListOut.append(sOut);
    }
    QString qsFileName = LoadFiles->qsProgramPath + "/data/TextOut.txt";
    bool result = cLoadFiles::saveStringListToFile(qsFileName, qslListOut);

    QString info = "execActionRemoveSquareBrackets(): save result ";
    if(result)info += "Ok"; else info += "Failure";
    emit setStatus(info);
}
