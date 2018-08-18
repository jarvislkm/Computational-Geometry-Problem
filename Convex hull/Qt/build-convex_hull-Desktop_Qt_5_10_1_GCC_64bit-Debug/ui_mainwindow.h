/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGraphicsView *graphicsView;
    QPushButton *pushButton;
    QLabel *label;
    QPushButton *load_first;
    QTextEdit *show_left;
    QPushButton *removeLeft;
    QTextEdit *show_left_2;
    QLabel *pointsLabel;
    QLabel *resultLabel;
    QPushButton *clear;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1104, 718);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        graphicsView = new QGraphicsView(centralWidget);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));
        graphicsView->setGeometry(QRect(50, 20, 481, 281));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(560, 390, 89, 25));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(50, 340, 551, 41));
        load_first = new QPushButton(centralWidget);
        load_first->setObjectName(QStringLiteral("load_first"));
        load_first->setGeometry(QRect(550, 330, 141, 25));
        show_left = new QTextEdit(centralWidget);
        show_left->setObjectName(QStringLiteral("show_left"));
        show_left->setGeometry(QRect(560, 20, 81, 271));
        removeLeft = new QPushButton(centralWidget);
        removeLeft->setObjectName(QStringLiteral("removeLeft"));
        removeLeft->setGeometry(QRect(550, 300, 89, 25));
        show_left_2 = new QTextEdit(centralWidget);
        show_left_2->setObjectName(QStringLiteral("show_left_2"));
        show_left_2->setGeometry(QRect(650, 20, 81, 271));
        pointsLabel = new QLabel(centralWidget);
        pointsLabel->setObjectName(QStringLiteral("pointsLabel"));
        pointsLabel->setGeometry(QRect(560, 0, 67, 17));
        resultLabel = new QLabel(centralWidget);
        resultLabel->setObjectName(QStringLiteral("resultLabel"));
        resultLabel->setGeometry(QRect(650, 0, 67, 17));
        clear = new QPushButton(centralWidget);
        clear->setObjectName(QStringLiteral("clear"));
        clear->setGeometry(QRect(540, 430, 89, 25));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1104, 22));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        pushButton->setText(QApplication::translate("MainWindow", "Save", nullptr));
        label->setText(QString());
        load_first->setText(QApplication::translate("MainWindow", "Load", nullptr));
        removeLeft->setText(QApplication::translate("MainWindow", "Undo", nullptr));
        pointsLabel->setText(QApplication::translate("MainWindow", "Points", nullptr));
        resultLabel->setText(QApplication::translate("MainWindow", "ch index", nullptr));
        clear->setText(QApplication::translate("MainWindow", "Clear", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
