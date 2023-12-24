/********************************************************************************
** Form generated from reading UI file 'frame.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRAME_H
#define UI_FRAME_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_Frame
{
public:
    QVBoxLayout *verticalLayout_4;
    QGridLayout *gridLayout_2;
    QLabel *POSVALY;
    QLabel *RENDERFACES;
    QLabel *RENDERSECTIONS;
    QLabel *FPS;
    QLabel *RENDERTIME;
    QLabel *POSVALZ;
    QLabel *POSVALX;
    QLabel *POS;
    QLabel *RENDERTIMEVAL;
    QLabel *RENDERFACESVAL;
    QLabel *FPSVAL;
    QLabel *RENDERSECTIONSVAL;
    QLabel *CURRENTTIME;
    QLabel *CURRENTTIMEVAL;

    void setupUi(QFrame *Frame)
    {
        if (Frame->objectName().isEmpty())
            Frame->setObjectName(QString::fromUtf8("Frame"));
        Frame->resize(521, 394);
        verticalLayout_4 = new QVBoxLayout(Frame);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        POSVALY = new QLabel(Frame);
        POSVALY->setObjectName(QString::fromUtf8("POSVALY"));

        gridLayout_2->addWidget(POSVALY, 1, 2, 1, 1);

        RENDERFACES = new QLabel(Frame);
        RENDERFACES->setObjectName(QString::fromUtf8("RENDERFACES"));

        gridLayout_2->addWidget(RENDERFACES, 3, 0, 1, 1);

        RENDERSECTIONS = new QLabel(Frame);
        RENDERSECTIONS->setObjectName(QString::fromUtf8("RENDERSECTIONS"));

        gridLayout_2->addWidget(RENDERSECTIONS, 3, 2, 1, 1);

        FPS = new QLabel(Frame);
        FPS->setObjectName(QString::fromUtf8("FPS"));

        gridLayout_2->addWidget(FPS, 0, 0, 1, 1);

        RENDERTIME = new QLabel(Frame);
        RENDERTIME->setObjectName(QString::fromUtf8("RENDERTIME"));

        gridLayout_2->addWidget(RENDERTIME, 2, 0, 1, 1);

        POSVALZ = new QLabel(Frame);
        POSVALZ->setObjectName(QString::fromUtf8("POSVALZ"));

        gridLayout_2->addWidget(POSVALZ, 1, 3, 1, 1);

        POSVALX = new QLabel(Frame);
        POSVALX->setObjectName(QString::fromUtf8("POSVALX"));

        gridLayout_2->addWidget(POSVALX, 1, 1, 1, 1);

        POS = new QLabel(Frame);
        POS->setObjectName(QString::fromUtf8("POS"));

        gridLayout_2->addWidget(POS, 1, 0, 1, 1);

        RENDERTIMEVAL = new QLabel(Frame);
        RENDERTIMEVAL->setObjectName(QString::fromUtf8("RENDERTIMEVAL"));

        gridLayout_2->addWidget(RENDERTIMEVAL, 2, 1, 1, 1);

        RENDERFACESVAL = new QLabel(Frame);
        RENDERFACESVAL->setObjectName(QString::fromUtf8("RENDERFACESVAL"));
        RENDERFACESVAL->setFocusPolicy(Qt::NoFocus);

        gridLayout_2->addWidget(RENDERFACESVAL, 3, 1, 1, 1);

        FPSVAL = new QLabel(Frame);
        FPSVAL->setObjectName(QString::fromUtf8("FPSVAL"));

        gridLayout_2->addWidget(FPSVAL, 0, 1, 1, 1);

        RENDERSECTIONSVAL = new QLabel(Frame);
        RENDERSECTIONSVAL->setObjectName(QString::fromUtf8("RENDERSECTIONSVAL"));

        gridLayout_2->addWidget(RENDERSECTIONSVAL, 3, 3, 1, 1);

        CURRENTTIME = new QLabel(Frame);
        CURRENTTIME->setObjectName(QString::fromUtf8("CURRENTTIME"));

        gridLayout_2->addWidget(CURRENTTIME, 4, 0, 1, 1);

        CURRENTTIMEVAL = new QLabel(Frame);
        CURRENTTIMEVAL->setObjectName(QString::fromUtf8("CURRENTTIMEVAL"));

        gridLayout_2->addWidget(CURRENTTIMEVAL, 4, 1, 1, 1);


        verticalLayout_4->addLayout(gridLayout_2);


        retranslateUi(Frame);

        QMetaObject::connectSlotsByName(Frame);
    } // setupUi

    void retranslateUi(QFrame *Frame)
    {
        Frame->setWindowTitle(QCoreApplication::translate("Frame", "Frame", nullptr));
        POSVALY->setText(QCoreApplication::translate("Frame", "0", nullptr));
        RENDERFACES->setText(QCoreApplication::translate("Frame", "RenderFace:", nullptr));
        RENDERSECTIONS->setText(QCoreApplication::translate("Frame", "RenderSecton:", nullptr));
        FPS->setText(QCoreApplication::translate("Frame", "FPS:", nullptr));
        RENDERTIME->setText(QCoreApplication::translate("Frame", "RenderTime:", nullptr));
        POSVALZ->setText(QCoreApplication::translate("Frame", "0", nullptr));
        POSVALX->setText(QCoreApplication::translate("Frame", "0", nullptr));
        POS->setText(QCoreApplication::translate("Frame", "POS:", nullptr));
        RENDERTIMEVAL->setText(QCoreApplication::translate("Frame", "0", nullptr));
        RENDERFACESVAL->setText(QCoreApplication::translate("Frame", "0", nullptr));
        FPSVAL->setText(QCoreApplication::translate("Frame", "1000", nullptr));
        RENDERSECTIONSVAL->setText(QCoreApplication::translate("Frame", "0", nullptr));
        CURRENTTIME->setText(QCoreApplication::translate("Frame", "CurrentTime", nullptr));
        CURRENTTIMEVAL->setText(QCoreApplication::translate("Frame", "0", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Frame: public Ui_Frame {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRAME_H
