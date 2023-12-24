/********************************************************************************
** Form generated from reading UI file 'bag.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BAG_H
#define UI_BAG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_Bag
{
public:
    QHBoxLayout *horizontalLayout;
    QTableWidget *bag;

    void setupUi(QFrame *Bag)
    {
        if (Bag->objectName().isEmpty())
            Bag->setObjectName(QString::fromUtf8("Bag"));
        Bag->resize(400, 300);
        horizontalLayout = new QHBoxLayout(Bag);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        bag = new QTableWidget(Bag);
        bag->setObjectName(QString::fromUtf8("bag"));
        bag->horizontalHeader()->setVisible(false);
        bag->verticalHeader()->setVisible(false);

        horizontalLayout->addWidget(bag);


        retranslateUi(Bag);

        QMetaObject::connectSlotsByName(Bag);
    } // setupUi

    void retranslateUi(QFrame *Bag)
    {
        Bag->setWindowTitle(QCoreApplication::translate("Bag", "Frame", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Bag: public Ui_Bag {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BAG_H
