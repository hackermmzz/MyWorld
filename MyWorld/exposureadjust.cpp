#include "exposureadjust.h"
#include "ui_exposureadjust.h"

ExposureAdjust::ExposureAdjust(QWidget *parent)
    : QFrame(parent)
    , ui(new Ui::ExposureAdjust)
{
    ui->setupUi(this);
}

ExposureAdjust::~ExposureAdjust()
{
    delete ui;
}
