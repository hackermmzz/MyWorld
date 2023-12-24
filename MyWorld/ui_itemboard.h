/********************************************************************************
** Form generated from reading UI file 'itemboard.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ITEMBOARD_H
#define UI_ITEMBOARD_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include"BagButton.h"
QT_BEGIN_NAMESPACE

class Ui_ItemBoard
{
public:
    QHBoxLayout *horizontalLayout_2;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    BagButton *item[9];
    QLabel* num[9];
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *verticalLayout_4;
    QVBoxLayout *verticalLayout_5;
    QVBoxLayout *verticalLayout_6;
    QVBoxLayout *verticalLayout_7;
    QVBoxLayout *verticalLayout_8;
    QVBoxLayout *verticalLayout_9;
    void setupUi(QFrame *ItemBoard)
    {
        if (ItemBoard->objectName().isEmpty())
            ItemBoard->setObjectName(QString::fromUtf8("ItemBoard"));
        ItemBoard->resize(766, 300);
        horizontalLayout_2 = new QHBoxLayout(ItemBoard);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        item[0] = new BagButton(ItemBoard);
        item[0]->setObjectName(QString::fromUtf8("item0"));

        verticalLayout->addWidget(item[0]);

        num[0] = new QLabel(ItemBoard);
        num[0]->setObjectName(QString::fromUtf8("num0"));

        verticalLayout->addWidget(num[0]);


        horizontalLayout->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        item[1]= new BagButton(ItemBoard);
        item[1]->setObjectName(QString::fromUtf8("item1"));

        verticalLayout_2->addWidget(item[1]);

        num[1] = new QLabel(ItemBoard);
        num[1]->setObjectName(QString::fromUtf8("num1"));

        verticalLayout_2->addWidget(num[1]);


        horizontalLayout->addLayout(verticalLayout_2);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        item[2] = new BagButton(ItemBoard);
        item[2]->setObjectName(QString::fromUtf8("item2"));

        verticalLayout_3->addWidget(item[2]);

        num[2] = new QLabel(ItemBoard);
        num[2]->setObjectName(QString::fromUtf8("num2"));

        verticalLayout_3->addWidget(num[2]);


        horizontalLayout->addLayout(verticalLayout_3);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        item[3] = new BagButton(ItemBoard);
        item[3]->setObjectName(QString::fromUtf8("item3"));

        verticalLayout_4->addWidget(item[3]);

        num[3] = new QLabel(ItemBoard);
        num[3]->setObjectName(QString::fromUtf8("num3"));

        verticalLayout_4->addWidget(num[3]);


        horizontalLayout->addLayout(verticalLayout_4);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        item[4] = new BagButton(ItemBoard);
        item[4]->setObjectName(QString::fromUtf8("item4"));

        verticalLayout_5->addWidget(item[4]);

        num[4] = new QLabel(ItemBoard);
        num[4]->setObjectName(QString::fromUtf8("num4"));

        verticalLayout_5->addWidget(num[4]);


        horizontalLayout->addLayout(verticalLayout_5);

        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        item[5] = new BagButton(ItemBoard);
        item[5]->setObjectName(QString::fromUtf8("item5"));

        verticalLayout_6->addWidget(item[5]);

        num[5] = new QLabel(ItemBoard);
        num[5]->setObjectName(QString::fromUtf8("num5"));

        verticalLayout_6->addWidget(num[5]);


        horizontalLayout->addLayout(verticalLayout_6);

        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        item[6] = new BagButton(ItemBoard);
        item[6]->setObjectName(QString::fromUtf8("item6"));

        verticalLayout_7->addWidget(item[6]);

        num[6] = new QLabel(ItemBoard);
        num[6]->setObjectName(QString::fromUtf8("num6"));

        verticalLayout_7->addWidget(num[6]);


        horizontalLayout->addLayout(verticalLayout_7);

        verticalLayout_8 = new QVBoxLayout();
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        item[7] = new BagButton(ItemBoard);
        item[7]->setObjectName(QString::fromUtf8("item7"));

        verticalLayout_8->addWidget(item[7]);

        num[7] = new QLabel(ItemBoard);
        num[7]->setObjectName(QString::fromUtf8("num7"));

        verticalLayout_8->addWidget(num[7]);


        horizontalLayout->addLayout(verticalLayout_8);

        verticalLayout_9 = new QVBoxLayout();
        verticalLayout_9->setObjectName(QString::fromUtf8("verticalLayout_9"));
        item[8] = new BagButton(ItemBoard);
        item[8]->setObjectName(QString::fromUtf8("item8"));

        verticalLayout_9->addWidget(item[8]);

        num[8] = new QLabel(ItemBoard);
        num[8]->setObjectName(QString::fromUtf8("num8"));

        verticalLayout_9->addWidget(num[8]);


        horizontalLayout->addLayout(verticalLayout_9);


        horizontalLayout_2->addLayout(horizontalLayout);


        retranslateUi(ItemBoard);

        QMetaObject::connectSlotsByName(ItemBoard);
    } // setupUi

    void retranslateUi(QFrame *ItemBoard)
    {
        ItemBoard->setWindowTitle(QCoreApplication::translate("ItemBoard", "Frame", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ItemBoard: public Ui_ItemBoard {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ITEMBOARD_H
