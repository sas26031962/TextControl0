#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    LoadFiles = new cLoadFiles();

    connect(this, &MainWindow::setStatus, this, &MainWindow::execSetStatus);
    connect(ui->actionLoadFromFile, &QAction::triggered, this, &MainWindow::execActionLoadFromFile);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::execSetStatus(QString s)
{
    qDebug() << s;
}

void MainWindow::execActionLoadFromFile(bool x)
{
    QString qsFileName = "./data/Text.txt";
    QStringList qslList = cLoadFiles::loadStringListFromFile(qsFileName);
    ui->textBrowser->clear();
    foreach (auto s, qslList)
    {
        ui->textBrowser->append(s);
    }
    emit setStatus("execActionLoadFiles() > load: " + QString::number(qslList.count()) + " lines");
}
