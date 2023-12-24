/********************************************************************************
** Form generated from reading UI file 'workspaceboard.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WORKSPACEBOARD_H
#define UI_WORKSPACEBOARD_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include"BagButton.h"
QT_BEGIN_NAMESPACE

class Ui_WorkSpaceBoard
{
public:
    QVBoxLayout *verticalLayout_2;
    QGridLayout *Grid;
    QVBoxLayout *verticalLayout;
    BagButton*target;
    QLabel *number;
    BagButton* source[9];
    QRadioButton *exit;
    QSpacerItem *verticalSpacer;
    QTableWidget *Bag;
    void setupUi(QFrame *WorkSpaceBoard)
    {
        if (WorkSpaceBoard->objectName().isEmpty())
            WorkSpaceBoard->setObjectName(QString::fromUtf8("WorkSpaceBoard"));
        WorkSpaceBoard->resize(400, 292);
        verticalLayout_2 = new QVBoxLayout(WorkSpaceBoard);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        Grid = new QGridLayout();
        Grid->setObjectName(QString::fromUtf8("Grid"));
        source[2] = new BagButton(WorkSpaceBoard);
        source[2]->setObjectName(QString::fromUtf8("source2"));

        Grid->addWidget(source[2], 0, 2, 1, 1);

        source[4] = new BagButton(WorkSpaceBoard);
        source[4]->setObjectName(QString::fromUtf8("source4"));

        Grid->addWidget(source[4], 1, 1, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        target = new BagButton(WorkSpaceBoard);
        target->setObjectName(QString::fromUtf8("target"));

        verticalLayout->addWidget(target);

        number = new QLabel(WorkSpaceBoard);
        number->setObjectName(QString::fromUtf8("number"));

        verticalLayout->addWidget(number);


        Grid->addLayout(verticalLayout, 1, 3, 1, 1);

        source[8] = new BagButton(WorkSpaceBoard);
        source[8]->setObjectName(QString::fromUtf8("source8"));

        Grid->addWidget(source[8], 2, 2, 1, 1);

        source[1] = new BagButton(WorkSpaceBoard);
        source[1]->setObjectName(QString::fromUtf8("source1"));

        Grid->addWidget(source[1], 0, 1, 1, 1);

        source[5] = new BagButton(WorkSpaceBoard);
        source[5]->setObjectName(QString::fromUtf8("source5"));

        Grid->addWidget(source[5], 1, 2, 1, 1);

        source[3] = new BagButton(WorkSpaceBoard);
        source[3]->setObjectName(QString::fromUtf8("source3"));

        Grid->addWidget(source[3], 1, 0, 1, 1);

        source[6] = new BagButton(WorkSpaceBoard);
        source[6]->setObjectName(QString::fromUtf8("source6"));

        Grid->addWidget(source[6], 2, 0, 1, 1);

        source[7] = new BagButton(WorkSpaceBoard);
        source[7]->setObjectName(QString::fromUtf8("source7"));

        Grid->addWidget(source[7], 2, 1, 1, 1);

        source[0] = new BagButton(WorkSpaceBoard);
        source[0]->setObjectName(QString::fromUtf8("source0"));

        Grid->addWidget(source[0], 0, 0, 1, 1);

        exit = new QRadioButton(WorkSpaceBoard);
        exit->setObjectName(QString::fromUtf8("exit"));

        Grid->addWidget(exit, 0, 4, 1, 1);


        verticalLayout_2->addLayout(Grid);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Minimum);

        verticalLayout_2->addItem(verticalSpacer);

        Bag = new QTableWidget(WorkSpaceBoard);
        if (Bag->columnCount() < 16)
            Bag->setColumnCount(16);
        if (Bag->rowCount() < 16)
            Bag->setRowCount(16);
        Bag->setObjectName(QString::fromUtf8("Bag"));
        Bag->setRowCount(16);
        Bag->setColumnCount(16);

        verticalLayout_2->addWidget(Bag);


        retranslateUi(WorkSpaceBoard);

        QMetaObject::connectSlotsByName(WorkSpaceBoard);
    } // setupUi

    void retranslateUi(QFrame *WorkSpaceBoard)
    {
        WorkSpaceBoard->setWindowTitle(QCoreApplication::translate("WorkSpaceBoard", "Frame", nullptr));
        number->setText(QCoreApplication::translate("WorkSpaceBoard", "Nums:0", nullptr));
        exit->setText(QCoreApplication::translate("WorkSpaceBoard", "exit", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WorkSpaceBoard: public Ui_WorkSpaceBoard {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WORKSPACEBOARD_H
