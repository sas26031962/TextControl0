#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include <QStatusBar>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    vmCurrentListIndex.install(0);

    LoadFiles = new cLoadFiles(ui->textBrowserData);

    connect(this, &MainWindow::setStatus, this, &MainWindow::execSetStatus);
    connect(ui->actionLoadFromFile, &QAction::triggered, this, &MainWindow::execActionLoadFromFile);
    connect(ui->actionRemoveSquareBrackets, &QAction::triggered, this, &MainWindow::execActionRemoveSquareBrackets);
    connect(ui->actionSeparateStrings, &QAction::triggered, this, &MainWindow::execActionSeparateStrings);

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
        cLoadFiles::IsLinux = false;
        cLoadFiles::IsWindows = true;
    #elif defined(Q_OS_LINUX)
        qDebug() << "Running on Linux";
        cLoadFiles::IsLinux = true;
        cLoadFiles::IsWindows = false;
    #else
        qDebug() << "Running on unknown OS";
    #endif

    QString qsDirectory = fileInfo.path();
    if(cLoadFiles::IsLinux)
    {
        LoadFiles->qsProgramPath = qsDirectory;
        qsCtorMessage = "Ctor > OS Linux detected";
    }
    else if(cLoadFiles::IsWindows)
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

    qsParametersFileName = LoadFiles->qsProgramPath + qsParametersFileName;

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
    QPushButton * pbNextString = new QPushButton("След.");
    pbSearchParameter->setCursor(Qt::PointingHandCursor);
    connect(pbNextString, static_cast<void(QPushButton::*)()>(&QPushButton::pressed),this, [this](){
        qDebug() << "PushButton 'Next' click";
        execActionSelectNextString(false);
    });
    ui->statusBar->addWidget(pbNextString);
    //---
    QPushButton * pbPreviousString = new QPushButton("Пред.");
    pbSearchParameter->setCursor(Qt::PointingHandCursor);
    connect(pbPreviousString, static_cast<void(QPushButton::*)()>(&QPushButton::pressed),this, [this](){
        qDebug() << "PushButton 'Previous' click";
        execActionSelectPreviousString(false);
    });
    ui->statusBar->addWidget(pbPreviousString);
    //---
    QPushButton * pbStoreString = new QPushButton("Сохр.");
    pbStoreString->setCursor(Qt::PointingHandCursor);
    connect(pbStoreString, static_cast<void(QPushButton::*)()>(&QPushButton::pressed),this, [this](){
        qDebug() << "PushButton 'Store' click";
        execActionStoreString(false);
    });
    ui->statusBar->addWidget(pbStoreString);
    //---

    QPushButton * pbInsertToList = new QPushButton("Доб.в список");
    pbInsertToList->setCursor(Qt::PointingHandCursor);
    connect(pbInsertToList, static_cast<void(QPushButton::*)()>(&QPushButton::pressed),this, [this](){
        qDebug() << "PushButton 'Append to list' click";
        execActionAppendToList(false);
    });
    ui->statusBar->addWidget(pbInsertToList);
    //---

    //---Выбор кодировки---
    connect(ui->radioButtonUTF8, &QRadioButton::toggled, this, [this](bool checked) {
        if (checked)
        {
            cLoadFiles::IsUTF8 = true;
            cLoadFiles::IsWindows1251 = false;
            qDebug() << "Select UTF-8 code page";
        }
    });

    connect(ui->radioButtonWindows1251, &QRadioButton::toggled, this, [this](bool checked) {
        if (checked)
        {
            cLoadFiles::IsUTF8 = false;
            cLoadFiles::IsWindows1251 = true;
            qDebug() << "Select Windows-1251 code page";
        }
    });

    qslParameters = cLoadFiles::loadStringListFromFile(qsParametersFileName);
    ui->comboBoxParameter->clear();
    ui->comboBoxParameter->addItems(qslParameters);

    //Финальное сообщение конструктора
    emit setStatus(qsCtorMessage);

}//End of ctor

MainWindow::~MainWindow()
{
    delete ui;
}

//=============================================================================
// СЛОТЫ
//=============================================================================

void MainWindow::execSetStatus(QString s)
{
    qDebug() << s;
    ui->textBrowserLog->append(s);
}

//=============================================================================
// АКЦИИ
//=============================================================================

void MainWindow::execActionLoadFromFile(bool x)
{
    if(!x)
    {
        QString info = "execActionLoadFiles() > ";
        QString qsFileName = LoadFiles->qsProgramPath + "/data/Text.txt";
        info += "FileName=";
        info += qsFileName;

        int n = LoadFiles->loadStringsFromFile(qsFileName);
        if(n > 0)
        {
            ListCount = n;
            //Установка курсора на начало текста
            vmCurrentListIndex.install(0);
            setCursorPlace();
        }
        else
        {
            info += " no strings loaded!!!";
        }
        emit setStatus(info);
    }
}

void MainWindow::execActionRemoveSquareBrackets(bool x)
{
    if(!x)
    {
        QString info = "execActionRemoveSquareBrackets() > ";
        QStringList qslListOut;
        qslListOut.clear();
        ui->textBrowserData->clear();

        foreach (auto s, LoadFiles->qslListIn)
        {
            QString sOut = removeSquareBracketAndColonToDefis(s);
            qslListOut.append(sOut);
            ui->textBrowserData->append(sOut);
        }

        //Установка курсора на начало текста
        vmCurrentListIndex.install(0);
        setCursorPlace();

        //Сохранение результата в файл
        QString qsFileName = LoadFiles->qsProgramPath + "/data/Text.txt";
        bool result = cLoadFiles::saveStringListToFile(qsFileName, qslListOut);

        info += "Save result ";
        if(result)info += "Ok"; else info += "Failure";
        emit setStatus(info);
    }
}

void MainWindow::execActionEmbraceSquareBrackets(bool x)
{
    if(!x)
    {
        QString info = "execActionEmbraceSquareBrackets";
        //---
        QString qsSource = ui->LineEditSource->text();
        QString qsParameter = ui->LineEditParameter->text();
        if(qsParameter.count() > 0)
        {
            QVector<int> * qvOutput = new QVector<int>();
            qvOutput->clear();

            int x = 0;//Индекс первого вхождения подстроки

            QString qsTail = "";
            QString qsResult = "";

            while(x >= 0)
            {
                if(qvOutput->count() > 0)
                {
                    //--- Повторные вхождения
                    x = qsTail.indexOf(qsParameter);
                    qDebug() << "X=" << x << " branch 1";
                    if(x >= 0)
                    {
                        qsResult += qsTail.mid(0, x);
                        qsResult += "[[";
                        qsResult += qsParameter;
                        qsResult += "]]";

                        qsTail = qsTail.mid(x + qsParameter.length());
                        qvOutput->append(x);
                    }
                    //---
                }
                else
                {
                    //--- Первое вхождение
                    x = qsSource.indexOf(qsParameter);
                    qDebug() << "X=" << x << " branch 0";
                    if(x >= 0)
                    {
                        qsResult = qsSource.mid(0, x);
                        qsResult += "[[";
                        qsResult += qsParameter;
                        qsResult += "]]";
                        qsTail = qsSource.mid(x + qsParameter.length());
                        qvOutput->append(x);
                    }
                    else
                    {
                        qsTail = qsSource;
                    }
                    //---
                }
            }//End of while(x >= 0)

            qsResult += qsTail;

            //ui->labelResult->setText(qsResult);
            ui->LineEditSource->setText(qsResult);

            qDebug() << "End of process, count:" << qvOutput->count();

        }//End of if(qsParameter.count() > 0)
        else
        {
            info += " > Empty parameter: nothing to do";
        }
        //---
        emit setStatus(info);
    }
}

void MainWindow::execActionSwapParts(bool x)
{
    if(!x)
    {
        QString info = "execActionSwapParts\n";
        QString result = swapNameFamily(ui->LineEditParameter->text());
        ui->LineEditParameter->setText(result);
        //info += "Result=";
        //info += result;
        emit setStatus(info);
    }
}

void MainWindow::execActionSearchPattern(bool x)
{
    QString info = "execActionSearchPattern:";
    //---
    QString qsSource = ui->LineEditSource->text();
    QString qsParameter = ui->LineEditParameter->text();
    if(qsParameter.count())
    {
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
    }
    else
    {
        info += "Parameter is emptyy: nothing to do";
    }

    emit setStatus(info);
}

void MainWindow::execActionSelectNextString(bool x)
{
    if(!x)
    {
        QString info = "MainWindow > Select next String: ";
        if(ListCount > 0)
        {
            int x = vmCurrentListIndex.Current;
            x++;
            if(x >= ListCount) x = ListCount - 1;
            vmCurrentListIndex.push(x);
            setCursorPlace();
            info += QString::number(vmCurrentListIndex.Current);
        }
        else
        {
            info += ": empty list, nothing to do";
        }
        emit setStatus(info);
    }
}

void MainWindow::execActionSelectPreviousString(bool x)
{
    if(!x)
    {
        QString info = "MainWindow > Select previous string: ";
        if(ListCount > 0)
        {
            int x = vmCurrentListIndex.Current;
            x--;
            if(x < 0) x = 0;
            vmCurrentListIndex.push(x);
            setCursorPlace();
            info += QString::number(vmCurrentListIndex.Current);
        }
        else
        {
            info += ": empty list, nothing to do";
        }
        emit setStatus(info);
    }
}

void MainWindow::execActionStoreString(bool x)
{
    if(!x)
    {
        QString info = "MainWindow > Store String ";
        //---
        QString s = ui->LineEditSource->text();
        qDebug() << "New text for replace: " << s;
        LoadFiles->qslListIn.replace(vmCurrentListIndex.Current, s);

        //Замена строки в блоке на экране
        QStringList lines = ui->textBrowserData->toPlainText().split('\n');
        if (vmCurrentListIndex.Current >= 0 && vmCurrentListIndex.Current < lines.size())
        {
            QString s = LoadFiles->qslListIn.at(vmCurrentListIndex.Current);//"New string";//ui->LineEditParameter->text();
            lines[vmCurrentListIndex.Current] = s;
            ui->textBrowserData->setPlainText(lines.join('\n'));
            setCursorPlace();
        }
        //Сохранение результата в файл
        QString qsFileName = LoadFiles->qsProgramPath + "/data/Text.txt";
        bool result = cLoadFiles::saveStringListToFile(qsFileName, LoadFiles->qslListIn);

        info += "Save result ";
        if(result)info += "Ok"; else info += "Failure";
        //---
        emit setStatus(info);
    }
}

void MainWindow::execActionAppendToList(bool x)
{
    if(!x)
    {
        QString info = "MainWindow > Append to list:";
        //---
        QString s = ui->LineEditParameter->text();
        if(s.length() > 0)
        {
            if(qslParameters.contains(s))
            {
                info += s;
                info += " exist in this list, nothing to do!";
            }
            else
            {
                qslParameters.append(s);
                bool x = cLoadFiles::saveStringListToFile(qsParametersFileName, qslParameters);
                ui->comboBoxParameter->addItem(s);
                info += s;
                info += ", strings count=";
                info += QString::number(ui->comboBoxParameter->count());
                if(x)
                {
                    info += " stored to file:";
                    info += qsParametersFileName;
                }
            }
        }
        else
        {
            info += " empty string, nothing to do";
        }

        //---
        emit setStatus(info);
    }
}


void MainWindow::execActionSeparateStrings(bool x)
{
    if(!x)
    {
        QString info = "MainWindow > Separate strings:";
        //---
        QStringList qslListOut;
        qslListOut.clear();
        ui->textBrowserData->clear();
        int Count = 0;

        foreach (auto s, LoadFiles->qslListIn)
        {
            int x = s.indexOf("] ");
            if(x > 0)
            {
                QString qsHead = s.mid(0, x);
                QString qsTail = s.mid(x + 1);
                qDebug() << "Head0=" << qsHead << " Tail0=" << qsTail;
                qslListOut.append(qsHead);
                ui->textBrowserData->append(qsHead);
                while( x > 0)
                {
                    Count++;
                    x = qsTail.indexOf("] ");
                    qsHead = qsTail.mid(0, x);
                    qslListOut.append(qsHead);
                    ui->textBrowserData->append(qsHead);
                    qDebug() << "Head1=" << qsHead;
                    qsTail = qsTail.mid(x + 1);
                }
                qslListOut.append(qsTail);
                ui->textBrowserData->append(qsTail);
                qDebug() << "TailLast=" << qsTail;

            }
            else
            {
                qslListOut.append(s);
                ui->textBrowserData->append(s);
            }
        }//End of foreach (auto s, LoadFiles->qslListIn)

        info += " Count=";
        info += QString::number(Count);

        LoadFiles->qslListIn = qslListOut;
        //---
        emit setStatus(info);
    }
}

//=============================================================================
// МЕТОДЫ
//=============================================================================

QString MainWindow::removeSquareBracketAndColonToDefis(QString s)
{
    QString qsOut = "";
    int ColonIndex = s.indexOf(':');
    int LeftBracketIndex = s.indexOf('[');
    int RightBracketIndex = s.indexOf(']');
    QString Acc = "";
    if(ColonIndex > 0)
    {
        Acc = s.mid(0,ColonIndex);
        Acc.append(" -");
        qDebug() << "Head=" << Acc;
        qsOut += Acc;

        Acc = s.mid(ColonIndex + 1, (LeftBracketIndex - ColonIndex - 1));
        qDebug() << "Neck=" << Acc;
        qsOut += Acc;

        Acc = s.mid(LeftBracketIndex + 1, (RightBracketIndex - LeftBracketIndex - 1));
        qDebug() << "Middle=" << Acc;
        qsOut += Acc;

        Acc = s.mid(RightBracketIndex + 1);
        qDebug() << "Tail=" << Acc;
        qsOut += Acc;
    }
    else
    {
        Acc = s.mid(0,LeftBracketIndex);
        qDebug() << "Head=" << Acc;
        qsOut += Acc;

        Acc = s.mid(LeftBracketIndex + 1, (RightBracketIndex - LeftBracketIndex - 1));
        qDebug() << "Middle=" << Acc;
        qsOut += Acc;

        Acc = s.mid(RightBracketIndex + 1);
        qDebug() << "Tail=" << Acc;
        qsOut += Acc;
    }
    return qsOut;
}

bool MainWindow::safeColorLine(QTextBrowser *textBrowser, int lineNumber, const QColor &color)
{
    if (!textBrowser || !textBrowser->document())
    {
        return false;
    }

    QTextDocument *doc = textBrowser->document();
    if (lineNumber < 0 || lineNumber >= doc->blockCount())
    {
        return false; // Строка не существует
    }

    QTextCursor cursor(doc);
    cursor.movePosition(QTextCursor::Start);

    for (int i = 0; i < lineNumber; ++i)
    {
        cursor.movePosition(QTextCursor::NextBlock);
    }

    cursor.select(QTextCursor::LineUnderCursor);

    QTextCharFormat format;
    format.setForeground(color);
    cursor.mergeCharFormat(format);

    return true;
}

bool MainWindow::setCursorPlace()
{
    bool x;
    QString s = LoadFiles->qslListIn.at(vmCurrentListIndex.Current);
    ui->LineEditSource->setText(s);
    x = safeColorLine(ui->textBrowserData, vmCurrentListIndex.Previous, Qt::black);
    x = x & safeColorLine(ui->textBrowserData, vmCurrentListIndex.Current, Qt::blue);
    return x;
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
