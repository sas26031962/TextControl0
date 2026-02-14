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
    QString qsFileName = "./data/Text.txt";
    int n = LoadFiles->loadStringsFromFile(qsFileName);
    emit setStatus("execActionLoadFiles() > load: " + QString::number(n) + " lines");
}

void MainWindow::execActionRemoveSquareBrackets(bool x)
{
    //QString sOut = LoadFiles->removeSquareBracket("One_Two_[Tree_Four]_Five");
    QString sOut = LoadFiles->removeSquareBracket(qsLine0);
    emit setStatus("execActionRemoveSquareBrackets(): " + sOut);
}
