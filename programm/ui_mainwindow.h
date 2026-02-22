/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionQuit;
    QAction *actionLoadFromFile;
    QAction *actionRemoveSquareBrackets;
    QWidget *centralWidget;
    QTextBrowser *textBrowserData;
    QTextBrowser *textBrowserLog;
    QLabel *labelDataCaption;
    QLabel *labelLogCaption;
    QLineEdit *LineEditSource;
    QLineEdit *LineEditParameter;
    QLabel *labelOptrationCaption;
    QLabel *labelParameterCaption;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuScenary;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1043, 637);
        actionQuit = new QAction(MainWindow);
        actionQuit->setObjectName(QStringLiteral("actionQuit"));
        actionLoadFromFile = new QAction(MainWindow);
        actionLoadFromFile->setObjectName(QStringLiteral("actionLoadFromFile"));
        actionRemoveSquareBrackets = new QAction(MainWindow);
        actionRemoveSquareBrackets->setObjectName(QStringLiteral("actionRemoveSquareBrackets"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        textBrowserData = new QTextBrowser(centralWidget);
        textBrowserData->setObjectName(QStringLiteral("textBrowserData"));
        textBrowserData->setGeometry(QRect(10, 40, 721, 451));
        textBrowserLog = new QTextBrowser(centralWidget);
        textBrowserLog->setObjectName(QStringLiteral("textBrowserLog"));
        textBrowserLog->setGeometry(QRect(750, 40, 281, 451));
        labelDataCaption = new QLabel(centralWidget);
        labelDataCaption->setObjectName(QStringLiteral("labelDataCaption"));
        labelDataCaption->setGeometry(QRect(14, 10, 721, 20));
        labelDataCaption->setStyleSheet(QStringLiteral("background-color: rgb(222, 235, 255);"));
        labelDataCaption->setAlignment(Qt::AlignCenter);
        labelLogCaption = new QLabel(centralWidget);
        labelLogCaption->setObjectName(QStringLiteral("labelLogCaption"));
        labelLogCaption->setGeometry(QRect(750, 10, 281, 16));
        labelLogCaption->setStyleSheet(QStringLiteral("background-color: rgb(222, 235, 255);"));
        labelLogCaption->setAlignment(Qt::AlignCenter);
        LineEditSource = new QLineEdit(centralWidget);
        LineEditSource->setObjectName(QStringLiteral("LineEditSource"));
        LineEditSource->setGeometry(QRect(10, 530, 731, 22));
        LineEditParameter = new QLineEdit(centralWidget);
        LineEditParameter->setObjectName(QStringLiteral("LineEditParameter"));
        LineEditParameter->setGeometry(QRect(750, 530, 281, 22));
        labelOptrationCaption = new QLabel(centralWidget);
        labelOptrationCaption->setObjectName(QStringLiteral("labelOptrationCaption"));
        labelOptrationCaption->setGeometry(QRect(10, 500, 721, 20));
        labelOptrationCaption->setStyleSheet(QStringLiteral("background-color: rgb(222, 235, 255);"));
        labelOptrationCaption->setAlignment(Qt::AlignCenter);
        labelParameterCaption = new QLabel(centralWidget);
        labelParameterCaption->setObjectName(QStringLiteral("labelParameterCaption"));
        labelParameterCaption->setGeometry(QRect(750, 500, 281, 16));
        labelParameterCaption->setStyleSheet(QStringLiteral("background-color: rgb(222, 235, 255);"));
        labelParameterCaption->setAlignment(Qt::AlignCenter);
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1043, 26));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuScenary = new QMenu(menuBar);
        menuScenary->setObjectName(QStringLiteral("menuScenary"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuScenary->menuAction());
        menuFile->addAction(actionQuit);
        menuScenary->addAction(actionLoadFromFile);
        menuScenary->addAction(actionRemoveSquareBrackets);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        actionQuit->setText(QApplication::translate("MainWindow", "\320\222\321\213\321\205\320\276\320\264", 0));
        actionLoadFromFile->setText(QApplication::translate("MainWindow", "\320\227\320\260\320\263\321\200\321\203\320\267\320\270\321\202\321\214 \320\270\320\267 \321\204\320\260\320\271\320\273\320\260", 0));
        actionRemoveSquareBrackets->setText(QApplication::translate("MainWindow", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214 \320\272\320\262\320\260\320\264\321\200\320\260\321\202\320\275\321\213\320\265 \321\201\320\272\320\276\320\261\320\272\320\270", 0));
        labelDataCaption->setText(QApplication::translate("MainWindow", "\320\224\320\260\320\275\320\275\321\213\320\265", 0));
        labelLogCaption->setText(QApplication::translate("MainWindow", "\320\226\321\203\321\200\320\275\320\260\320\273", 0));
        labelOptrationCaption->setText(QApplication::translate("MainWindow", "\320\241\321\202\321\200\320\276\320\272\320\260 \320\264\320\273\321\217 \321\200\320\260\320\261\320\276\321\202\321\213", 0));
        labelParameterCaption->setText(QApplication::translate("MainWindow", "\320\237\320\260\321\200\320\260\320\274\320\265\321\202\321\200", 0));
        menuFile->setTitle(QApplication::translate("MainWindow", "\320\244\320\260\320\271\320\273", 0));
        menuScenary->setTitle(QApplication::translate("MainWindow", "\320\241\321\206\320\265\320\275\320\260\321\200\320\270\320\271", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
