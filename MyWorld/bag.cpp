#include "bag.h"
#include "ui_bag.h"
Bag::Bag(QWidget *parent)
    : QFrame(parent)
    , ui(new Ui::Bag)
{
    ui->setupUi(this);
}

Bag::~Bag()
{
    delete ui;
}
