#include "itemboard.h"
#include "ui_itemboard.h"

ItemBoard::ItemBoard(QWidget *parent)
    : QFrame(parent)
    , ui(new Ui::ItemBoard)
{
    ui->setupUi(this);
    setFocusPolicy(Qt::NoFocus);
}

ItemBoard::~ItemBoard()
{
    delete ui;
}

