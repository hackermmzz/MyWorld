/********************************************************************************
** Form generated from reading UI file 'exposureadjust.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EXPOSUREADJUST_H
#define UI_EXPOSUREADJUST_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QSlider>

QT_BEGIN_NAMESPACE

class Ui_ExposureAdjust
{
public:
    QHBoxLayout *horizontalLayout;
    QSlider *Exposure;

    void setupUi(QFrame *ExposureAdjust)
    {
        if (ExposureAdjust->objectName().isEmpty())
            ExposureAdjust->setObjectName(QString::fromUtf8("ExposureAdjust"));
        ExposureAdjust->resize(288, 23);
        horizontalLayout = new QHBoxLayout(ExposureAdjust);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        Exposure = new QSlider(ExposureAdjust);
        Exposure->setObjectName(QString::fromUtf8("Exposure"));
        Exposure->setOrientation(Qt::Horizontal);

        horizontalLayout->addWidget(Exposure);


        retranslateUi(ExposureAdjust);

        QMetaObject::connectSlotsByName(ExposureAdjust);
    } // setupUi

    void retranslateUi(QFrame *ExposureAdjust)
    {
        ExposureAdjust->setWindowTitle(QCoreApplication::translate("ExposureAdjust", "Frame", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ExposureAdjust: public Ui_ExposureAdjust {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EXPOSUREADJUST_H
