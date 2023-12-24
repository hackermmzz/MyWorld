#ifndef EXPOSUREADJUST_H
#define EXPOSUREADJUST_H

#include <QFrame>
#include"ui_exposureadjust.h"
namespace Ui {
class ExposureAdjust;
}

class ExposureAdjust : public QFrame
{
    Q_OBJECT

public:
    explicit ExposureAdjust(QWidget *parent = nullptr);
    ~ExposureAdjust();
    Ui::ExposureAdjust *ui;
};

#endif // EXPOSUREADJUST_H
